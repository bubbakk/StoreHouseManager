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
                    QString _sourceID,
                    QJsonValue _data);

    enum messageTypeEnum { information, action };
    Q_ENUM(messageTypeEnum)

    QHostAddress _IPAddress;            // sender source IP
    QString _hostName;                  // sender host name
    QString _applicationName;           // sender application name
    uint16_t _applicationPID;           // sender application PID
    uint16_t _UTCTimestamp;             // sender UTC timestamp
    uint16_t _localTimestamp;           // sender local timestamp
    QString _readableLocalDateTime;     // sender local humand readable datetime
    messageTypeEnum _messageType;       // sender message type
    QString _sourceID;                  // sender identification
    QJsonValue _data;                   // data content

    QHostAddress getIPAddress() const;
    QString getHostName() const;
    QString getApplicationName() const;
    uint16_t getApplicationPID() const;
    uint32_t getUTCTimestamp() const;
    uint32_t getLocalTimestamp() const;
    QString getReadableDateTime() const;
    QString getSourceID() const;

private:
    QMetaObject dummyQMO = this->staticMetaObject;
    QMetaEnum dummyQME = dummyQMO.enumerator(dummyQMO.indexOfEnumerator("messageTypeEnum"));
};

#endif // SHMREQUEST_H
