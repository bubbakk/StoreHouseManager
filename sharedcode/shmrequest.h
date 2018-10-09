#ifndef SHMREQUEST_H
#define SHMREQUEST_H

#include <QObject>
#include <QMetaEnum>
#include <QString>
#include <QHostAddress>
#include <inttypes.h>


class SHMRequest : public QObject
{
    Q_OBJECT

public:
    SHMRequest();
    void setRequest(QString IPAddress,
                    QString hostName,
                    QString applicationName,
                    QString applicationPID,
                    QString UTCTimestamp,
                    QString localTimestamp,
                    QString readableDateTime,
                    QString messageType);

    enum messageTypeEnum { information, action };
    Q_ENUM(messageTypeEnum)

    QHostAddress IPAddress;
    QString hostName;
    QString applicationName;
    uint16_t applicationPID;
    uint16_t UTCTimestamp;
    uint16_t localTimestamp;
    QString readableDateTime;
    messageTypeEnum messageType;

    QHostAddress getIPAddress() const;
    QString getHostName() const;
    QString getApplicationName() const;
    uint16_t getApplicationPID() const;
    uint32_t getUTCTimestamp() const;
    uint32_t getLocalTimestamp() const;
    QString getReadableDateTime() const;

private:
    QMetaObject dummyQMO = this->staticMetaObject;
    QMetaEnum dummyQME = dummyQMO.enumerator(dummyQMO.indexOfEnumerator("messageTypeEnum"));
};

#endif // SHMREQUEST_H
