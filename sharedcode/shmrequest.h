#ifndef SHMREQUEST_H
#define SHMREQUEST_H

#include <QObject>
#include <QMetaEnum>
#include <QString>
#include <QHostAddress>
#include <inttypes.h>
#include <QJsonObject>


class SHMRequest : public QObject
{
    Q_OBJECT

public:
    SHMRequest(QObject *parent = nullptr);
    void setRequest(QString _IPAddress,
                    QString _hostName,
                    QString _applicationName,
                    QString _applicationPID,
                    QString _UTCTimestamp,
                    QString _localTimestamp,
                    QString _readableLocalDateTime,
                    QString _messageType,
                    QJsonValue _data);

    enum messageTypeEnum { information, action };
    Q_ENUM(messageTypeEnum)

    QHostAddress _IPAddress;
    QString _hostName;
    QString _applicationName;
    uint16_t _applicationPID;
    uint16_t _UTCTimestamp;
    uint16_t _localTimestamp;
    QString _readableLocalDateTime;
    messageTypeEnum _messageType;
    QJsonValue _data;

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
