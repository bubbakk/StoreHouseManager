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

    connect(this->_tcpServer, SIGNAL(newConnectionAccepted(QTcpSocket*)),      // new connection manager
            this, SLOT(slotTcpServerAcceptedConnection(QTcpSocket*)));
}

void tcpChat::slotTcpServerAcceptedConnection(QTcpSocket* socket)
{
    this->sendMessageToClient(socket, this->_chat->welcomeMsg);     // send welcome message to new client
}


void tcpChat::sendMessageToClient(QTcpSocket* socket, QString message)
{
    socket->write("\r\n");
    socket->write(message.toLatin1());
    socket->flush();
    socket->waitForBytesWritten();
}
