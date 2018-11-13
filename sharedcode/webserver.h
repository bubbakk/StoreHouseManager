#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>
#include <QDateTime>

#include "./3rdparty/qhttp/src/qhttpserver.hpp"
#include "./3rdparty/qhttp/src/qhttpserverconnection.hpp"
#include "./3rdparty/qhttp/src/qhttpserverrequest.hpp"
#include "./3rdparty/qhttp/src/qhttpserverresponse.hpp"

class webServer : public QObject
{
    Q_OBJECT
public:
    explicit webServer(QObject *parent = nullptr);
    bool start(qint16 port);

    class ClientHandler;

signals:

public slots:

private:
    qhttp::server::QHttpServer* _server;

private:
    qint32 _connectionCounter;
};

class webServerClientHandler : public QObject
{
    Q_OBJECT

public:
    explicit webServerClientHandler(qint32 id, qhttp::server::QHttpRequest* req, qhttp::server::QHttpResponse* res, QObject *parent = nullptr);
    ~webServerClientHandler();

private slots:


private:
    qint32 _connectionId;
};

#endif // WEBSERVER_H
