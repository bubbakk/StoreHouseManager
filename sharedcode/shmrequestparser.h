#ifndef SHMREQUESTPARSER_H
#define SHMREQUESTPARSER_H

#include <QObject>
#include <QStringList>
#include <QString>
#include <QDebug>
#include <QList>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonObject>

#include "../sharedcode/shmrequest.h"

class shmRequestParser : public QObject
{
    Q_OBJECT

public:
    explicit shmRequestParser(QObject *parent = nullptr);
    bool parse(QString);

    QString errorMessage = "";

    QList<SHMRequest *> getSHMRequestsList() const;

private:
    bool messageFormatCheck(QJsonObject* JSONObjectToCheck, QString* missingField);
    void extractSHMRequest(QJsonObject* JSONObjectSource, SHMRequest* request);

    QStringList mandatoryFields = { "IPAddress",
                                    "hostName",
                                    "applicationName",
                                    "applicationPID",
                                    "UTCTimestamp",
                                    "localTimestamp",
                                    "readableLocalDateTime",
                                    "messageType",
                                    "sourceID",
                                    "data"};

protected:
    QList<SHMRequest*> _SHMRequestsList;


signals:

public slots:

};

#endif // SHMREQUESTPARSER_H
