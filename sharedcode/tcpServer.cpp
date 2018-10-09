#include "tcpServer.h"

TCPServer::TCPServer(QObject *parent) : QObject(parent)
{
    qInfo() << "◌ Server che gestisce solo un client connesso: non va bene";
    qInfo() << "◌   Gestire così: https://www.qtcentre.org/threads/61677-QTcpServer-cleaning-up-when-clients-disconnect";
    qInfo() << "◌   eliminando il this->tcpServerConnection e sostituendolo con QTcpSocket* conn = qobject_cast<QTcpSocket*>(sender());";
    qInfo() << "◌   all'interno degli slot (gestori dei segnali)";
    qInfo() << "◌ Inoltre ogni socket DEVE AVERE il proprio buffer e i propri flag di comunicazione";
}

bool TCPServer::startListening(int port)
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        // attenzione: potrebbe prendere l'indirizzo VPN .... o no?
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty()) {
       ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }

    this->server.listen(QHostAddress::LocalHost, static_cast<quint16>(port));
    if (this->server.isListening() )
    {
        connect(&this->server, SIGNAL(newConnection()), this, SLOT(slotAcceptConnection()));
    }

    if ( !this->server.isListening() ) {
        this->errorMessage = "Impossibile avviare il server: " + this->server.errorString();
        qCritical().noquote() << this->errorMessage;
        return false;
    }

    qDebug("%s %s, port %d", "TCP server is listening to IP ", qPrintable(ipAddress), port);

    return true;
}

void TCPServer::slotAcceptConnection()
{
    QTcpSocket* socket = this->server.nextPendingConnection();
    connect(socket, SIGNAL(disconnected()), this, SLOT(slotClientDisconnect()));
    this->_clientsList.append(socket);

    emit newConnectionAccepted(socket);                 // emit newConnectionAccepted signal

    qDebug() << "Client " << this->_clientsList.count() << " connected... ";
}

void TCPServer::slotClientDisconnect()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(QObject::sender());

    int idx = this->_clientsList.indexOf(socket);
    if (idx!=-1)
        this->_clientsList.removeAt(idx);

    QString nth = "";
    idx++;
    if ( idx == 1) nth = "1-st";
    else if ( idx == 2 ) nth = "2-nd";
    else if ( idx == 3 ) nth = "3-rd";
    else nth = QString::number(idx) + "-th";

    qDebug().noquote() << "Disconnecting " << nth << " client... ";

    socket->deleteLater();
}
/*
void TCPServer::slotReadData()
{
    while (this->tcpServerConnection->canReadLine())
    {
        QString data = QString(this->tcpServerConnection->readLine());
        data = data.simplified();
        qDebug() << "Data line received: " << data;

        // HELP
        if ( data.compare(HELPCOMMAND, Qt::CaseInsensitive) == 0 )             // help requested (is the only case insenitive command)
        {
            // send commands list (help reply) to client
            this->sendMessageToClient(this->tcpServerConnection, this->helpCommandReply);
            return;
        }

        // QUIT | BYE
        if ( data.compare(QUITCOMMAND, Qt::CaseSensitive) == 0 ||
             data.compare(QUITCOMMAND1, Qt::CaseSensitive) == 0   )             // client disconnection requested
        {
            this->messageBuffer.clear();                                        // empty buffer
            this->messageStartLineFound = false;                                // reset start flag to false
            this->messageEndLineFound = false;                                  // reset end flag to false

            // good by client
            this->tcpServerConnection->write("bye.\n");
            this->tcpServerConnection->flush();
            this->tcpServerConnection->waitForBytesWritten();

            this->tcpServerConnection->disconnect();                            // disconnect socket
            this->tcpServerConnection->deleteLater();                           // destroy socket
            return;
        }

        // STARTLINECOMMAND
        if ( !this->messageStartLineFound )                                     // still not started message
        {
            if ( data.compare(STARTLINECOMMAND, Qt::CaseSensitive) == 0 )       // message START string found
            {
                qDebug() << "Message starts here";
                this->messageBuffer.clear();                                    // clear message buffer
                this->messageStartLineFound = true;                             // set started message flag
                return;                                                         // discard data
            }
            else
            {
                return;                                                         // discard data
            }
        }

        // ENDLINECOMMAND                                                       // if i'm here, the message already started
        if ( data.compare(ENDLINECOMMAND, Qt::CaseSensitive) == 0 )             // verify if message CLOSE is requested
        {
            qDebug() << "Message neds here";
            this->messageEndLineFound = true;                                   // set ended message flag
            emit(signalMessageReceived(&this->messageBuffer));                  // emit signalMessageReceived signal

            this->messageStartLineFound = false;                                // reset start flag to false
            this->messageEndLineFound = false;                                  // reset end flag to false

            qDebug() << "Complete message is " << this->messageBuffer;
            return;                                                             // discard data
        }

        qDebug() << "Appending data message";
        messageBuffer.append(data);                                             // append message data
    }
}

void TCPServer::sendMessageToClient(QTcpSocket* socket, QString message)
{
    socket->write("\n");
    socket->write(message.toLatin1());
    socket->flush();
    socket->waitForBytesWritten();
}
*/
TCPServer::~TCPServer()
{
    if ( this->server.isListening() )
    {
        this->server.close();
    }
}
