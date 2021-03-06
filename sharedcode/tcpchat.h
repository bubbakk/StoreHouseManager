#ifndef TCPCHAT_H
#define TCPCHAT_H

#include <QObject>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QMap>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "./tcpServer.h"
#include "./chat.h"

class tcpChat : public QObject
{
    Q_OBJECT

public:
    explicit tcpChat(int port = 12345, QObject *parent = nullptr);
    void startChat();
    void sendSimpleTextMessageToClient(QTcpSocket* socket, QString);
    void sendJSONMessageToClient(QTcpSocket* socket, QMap<QString, QString>);

signals:
    void messageReceived(QString message, QTcpSocket *socket);
    void printAllRequest(void);

public slots:

private slots:
    void slotTcpServerAcceptedConnection(QTcpSocket* socket);
    void slotManageMessageReceived(QTcpSocket* socket, QString message);
    void slotTcpServerClientDisconnetion(QTcpSocket*);

private:
    TCPServer *_tcpServer;
    chat *_chat;
    int _tcpPort;
    struct communication {
        QStringList* message;
        bool started;
        bool ended;
    };
    QMap<QTcpSocket*, communication*> _messageBuffers;
};

#endif // TCPCHAT_H
