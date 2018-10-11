#include "tcpchat.h"

tcpChat::tcpChat(int port, QObject *parent) : QObject(parent)
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
    connect(this->_tcpServer, SIGNAL(connetionClosed(QTcpSocket*, QString)),    // connection closed SLOT
            this, SLOT(slotTcpServerClientDisconnetion(QTcpSocket*, QString)));
}

void tcpChat::slotTcpServerAcceptedConnection(QTcpSocket* socket)
{
    communication* newCommm = new communication;                                // initializing communication structure
    newCommm->started = false;
    newCommm->ended   = false;
    newCommm->message = new QStringList();
    this->_messageBuffers[socket] = newCommm;                                   // coupling communication structure to socket

    this->sendMessageToClient(socket, this->_chat->welcomeMsg);                 // send welcome message to new client
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
        this->sendMessageToClient(socket, reply);
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


void tcpChat::sendMessageToClient(QTcpSocket* socket, QString message)
{
    socket->write(message.toLatin1());
    socket->write("\r\n");
    socket->flush();
    socket->waitForBytesWritten();
}
