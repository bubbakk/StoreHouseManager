#include "warehouserequestparser.h"

wareHouseRequestParser::wareHouseRequestParser(tcpChat* tcpChat, QObject *parent) : shmRequestParser(parent)
{
    this->_tcpChat = tcpChat;

    connect(this->_tcpChat, SIGNAL(messageReceived(QStringList*)),
            this, SLOT(parse(QStringList*)));
}

void wareHouseRequestParser::parse(QStringList* messageToParse)
{
    qDebug() << messageToParse;

    QString message = messageToParse->join("\n");

    this->parse(message);
}

void wareHouseRequestParser::parse(QString messageToParse)
{
    qDebug() << messageToParse;

    shmRequestParser::parse(messageToParse);
}
