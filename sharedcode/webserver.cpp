#include "webserver.h"

using namespace qhttp::server;

webServer::webServer(QObject *parent) : QObject(parent)
{
    // declare the web server
    this->_server = new QHttpServer(parent);
}

bool webServer::start(qint16 port)
{
    // set port
    QString portOrUnixSocket = QString().number(port);
    // set client number
    this->_connectionCounter = 0;

    this->_server->listen(portOrUnixSocket, [&](QHttpRequest* req, QHttpResponse* res){
        new webServerClientHandler(++this->_connectionCounter, req, res);
        // this ClientHandler object will be deleted automatically when:
        // socket disconnects (automatically after data has been sent to the client)
        //     -> QHttpConnection destroys
        //         -> QHttpRequest destroys -> ClientHandler destroys
        //         -> QHttpResponse destroys
        // all by parent-child model of QObject.
    });

    if ( !this->_server->isListening() ) {
        fprintf(stderr, "can not listen on %s!\n", qPrintable(portOrUnixSocket));
        return false;
    }

    return true;
}

/** connection class for gathering incoming chunks of data from HTTP client.
 * @warning please note that the incoming request instance is the parent of
 * this QObject instance. Thus this class will be deleted automatically.
 * */
webServerClientHandler::webServerClientHandler(qint32 idC, qhttp::server::QHttpRequest* req, qhttp::server::QHttpResponse* res, QObject *parent)
{
    // automatically collect http body(data) upto 1KB
    // req->collectData(1024);

    // print infos
    qDebug() << "Webserver connection info;";
    qDebug() << " client:      " << idC;
    qDebug() << " port:        " << req->remotePort();
    qDebug() << " from:        " << req->remoteAddress().toUtf8();
    qDebug() << " remote port: " << req->remotePort();
    qDebug() << " url:         " << req->url().toString();

    // connect event
    //connect(req, qhttp::QHttpAbstractInput::end() )

    // when all the incoming data are gathered, send some response to client.
    req->onEnd([this, req, res]() {
        QString message =
            QString("Hello World\n   time = %2\n")
            .arg(QLocale::c().toString(QDateTime::currentDateTime(),
                                   "yyyy-MM-dd hh:mm:ss")
        );

        res->setStatusCode(qhttp::ESTATUS_OK);
        res->addHeaderValue("content-length", message.size());
        res->end(message.toUtf8());

        if ( req->headers().keyHasValue("command", "quit") ) {
            qDebug("\n\na quit has been requested!\n");
        }
    });
};

webServerClientHandler::~webServerClientHandler()
{
    qDebug() << "Closing #" << this->_connectionId << " client connection";
}
