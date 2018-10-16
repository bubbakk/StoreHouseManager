#ifndef WAREHOUSEREQUESTPARSER_H
#define WAREHOUSEREQUESTPARSER_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "../sharedcode/shmrequestparser.h"
#include "../sharedcode/tcpchat.h"

class wareHouseRequestParser : public shmRequestParser
{
    Q_OBJECT

public:
    wareHouseRequestParser(tcpChat* tcpChat = nullptr, QObject* parent = nullptr);

private slots:
    void parse(QStringList* messageToParse);

private:
    tcpChat* _tcpChat;

    void parse(QString messageToParse);
};

#endif // WAREHOUSEREQUESTPARSER_H
