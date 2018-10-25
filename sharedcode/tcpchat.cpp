#include "tcpchat.h"

tcpChat::tcpChat(int port, QObject* parent) : QObject(parent)
{
    this->_tcpPort = port;
}

void tcpChat::startChat()
{

    this->_tcpServer = new TCPServer(this);                         // initialize TPC server
    this->_tcpServer->startListening(this->_tcpPort);               // start listening
    this->_chat = new chat(this);                                   // initialize chat
    this->_chat->setLineSeparator("\r\n");
    this->_chat->setWelcomeMsgApplicationName(QCoreApplication::applicationName());

    connect(this->_tcpServer, SIGNAL(newConnectionAccepted(QTcpSocket*)),       // new connection accepted SLOT
            this, SLOT(slotTcpServerAcceptedConnection(QTcpSocket*)));
    connect(this->_tcpServer, SIGNAL(messageReceived(QTcpSocket*, QString)),    // message received SLOT
            this, SLOT(slotManageMessageReceived(QTcpSocket*, QString)));
    connect(this->_tcpServer, SIGNAL(connetionClosed(QTcpSocket*)),    // connection closed SLOT
            this, SLOT(slotTcpServerClientDisconnetion(QTcpSocket*)));
}

void tcpChat::slotTcpServerAcceptedConnection(QTcpSocket* socket)
{
    communication* newCommm = new communication;                                // initializing communication structure
    newCommm->started = false;
    newCommm->ended   = false;
    newCommm->message = new QStringList();
    this->_messageBuffers[socket] = newCommm;                                   // coupling communication structure to socket

    this->sendSimpleTextMessageToClient(socket, this->_chat->welcomeMsg);                 // send welcome message to new client
}

void tcpChat::slotManageMessageReceived(QTcpSocket* socket, QString message)
{
    // STARTMSGCOMMAND
    if ( message == this->_chat->_commands["STARTMSGCOMMAND"] )
    {
        if ( !this->_messageBuffers[socket]->started )
        {
            this->_messageBuffers[socket]->started = true;
            this->_messageBuffers[socket]->ended = false;
            this->_messageBuffers[socket]->message->clear();
        }
        else
        {
            qWarning() << this->_chat->_commands["STARTMSGCOMMAND"] << " message received while already started";
        }
    }

    // ENDMSGCOMMAND
    if ( message == this->_chat->_commands["ENDMSGCOMMAND"] )
    {
        if ( this->_messageBuffers[socket]->started )
        {
            this->_messageBuffers[socket]->started = false;
            this->_messageBuffers[socket]->ended = false;

            qInfo() << "Message buffer closed";
            qInfo() << this->_messageBuffers[socket]->message->join(" ");

            // the message is closed: emit signal with the message pointer itself as parameter
            emit messageReceived(this->_messageBuffers[socket]->message->join("\n"), socket);
        }
        else
        {
            qWarning() << this->_chat->_commands["ENDMSGCOMMAND"] << " message received while not started";
        }
    }

    // append message to buffer if communication is started and not ended
    // and avoid enqueuing ENDMSGCOMMAND
    if ( this->_messageBuffers[socket]->started && !this->_messageBuffers[socket]->ended)
    {
        if ( message != this->_chat->_commands["STARTMSGCOMMAND"] )
        {
            this->_messageBuffers[socket]->message->append(message);
        }
    }

    // if a reply exists (not empty), send it
    QString reply = this->_chat->replyTo(message);
    if ( reply.compare("") != 0 )
    {
        this->sendSimpleTextMessageToClient(socket, reply);
    }

    // QUITCOMMAND
    if ( message == this->_chat->_commands["QUITCOMMAND"] ||  message == this->_chat->_commands["QUITCOMMAND_"] )
    {
        socket->close();
    }
}

void tcpChat::slotTcpServerClientDisconnetion(QTcpSocket* socket)
{
    // removing data (buffer included) associated to closed socket
    this->_messageBuffers.remove(socket);
}

void tcpChat::sendSimpleTextMessageToClient(QTcpSocket* socket, QString message)
{
    socket->write(message.toLatin1());
    socket->write("\r\n");
    socket->flush();
    socket->waitForBytesWritten();
}

void tcpChat::sendJSONMessageToClient(QTcpSocket *socket, QMap<QString, QString> values)
{
    // prepare JSON reply
    QJsonObject firstLevel;
    QJsonObject serverReplyDataField;
    QJsonObject dataField;
    for(auto e : values.toStdMap())
    {
        if (e.first == "requestReferenceID")
        {
            serverReplyDataField.insert("ReplyToID", QJsonValue(e.second));
        } else
        {
            dataField.insert(e.first, QJsonValue(e.second));
        }
    }
    serverReplyDataField.insert("applicationPID", QJsonValue(QCoreApplication::applicationPid()));
    serverReplyDataField.insert("UTCTimestamp", QJsonValue(QDateTime::currentSecsSinceEpoch()));
    serverReplyDataField.insert("localTimestamp", "TODO");
    serverReplyDataField.insert("readableLocalDateTime", QJsonValue(QDateTime::currentDateTime().toString()));
    serverReplyDataField.insert("data", dataField);

    firstLevel.insert("serverReplyData", serverReplyDataField);

    QJsonDocument messageToSend(firstLevel);

    socket->write(messageToSend.toJson(QJsonDocument::Compact));
    socket->write("\r\n");
    socket->flush();
    socket->waitForBytesWritten();
}
