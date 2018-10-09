#ifndef TCPCHAT_H
#define TCPCHAT_H

#include <QObject>
#include <QTcpSocket>
#include <QCoreApplication>

#include "./tcpServer.h"
#include "./chat.h"

class tcpChat : public QObject
{
    Q_OBJECT

public:
    explicit tcpChat(int port = 12345, QObject *parent = nullptr);
    void startChat();

signals:

public slots:

private slots:
    void slotTcpServerAcceptedConnection(QTcpSocket* socket);

private:
    TCPServer *_tcpServer;
    chat *_chat;
    int _tcpPort;
    QMap<QTcpSocket*, chat*> _clientsCommunication;

    void sendMessageToClient(QTcpSocket* socket, QString message);
};

#endif // TCPCHAT_H
