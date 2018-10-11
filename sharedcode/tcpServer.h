#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>

#define HELPCOMMAND       "HELP"
#define STARTLINECOMMAND  "SHM_MSG_STA"
#define ENDLINECOMMAND    "SHM_MSG_STO"
#define QUITCOMMAND       "QUIT"
#define QUITCOMMAND1      "BYE"

class TCPServer : public QObject
{
    Q_OBJECT

public:
    explicit TCPServer(QObject *parent = nullptr);
    ~TCPServer();
    bool startListening(int port);

    QTcpServer server;

signals:
    void newConnectionAccepted(QTcpSocket* socket);
    void messageReceived(QTcpSocket* socket, QString message);
    void connetionClosed(QTcpSocket* socket);

public slots:


private slots:
    void slotAcceptConnection(void);
    void slotClientDisconnect(QTcpSocket* socket = nullptr);
    void slotReadReady(void);

private:
    int port = 0;
    QString serverName;
    QString errorMessage;
    QString serverWelcomeMessage;
    QString helpCommandReply;


    QList<QTcpSocket*> _clientsList;
    QStringList messageBuffer;

    void sendMessageToClient(QTcpSocket* socket, QString message);
};

#endif // TCPSERVER_H
