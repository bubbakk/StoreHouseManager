#include "shmrequest.h"

SHMRequest::SHMRequest(QObject *parent) : QObject (parent)
{

}

void SHMRequest::setRequest(QString IPAddress,
                            QString hostName,
                            QString applicationName,
                            QString applicationPID,
                            QString UTCTimestamp,
                            QString localTimestamp,
                            QString readableLocalDateTime,
                            QString messageType,
                            QJsonValue data)
{
    qInfo().noquote() << "◌ Implementare controlli sull'assegnazione in SHMRequest::setRequest()";

    this->_IPAddress.setAddress(IPAddress);                                                          // conversion to QHostAddress
    this->_hostName = hostName;
    this->_applicationName = applicationName;
    this->_applicationPID = applicationPID.toUShort();                                               // conversion to uint16_t
    this->_UTCTimestamp = UTCTimestamp.toUShort();                                                   // conversion to uint32_t
    this->_localTimestamp = localTimestamp.toUShort();                                               // conversion to uint32_t
    this->_readableLocalDateTime = readableLocalDateTime;
    this->_messageType = static_cast<messageTypeEnum>(dummyQME.keyToValue(messageType.toLatin1()));  // conversion to enum
    this->_data = data;
}

uint16_t SHMRequest::getApplicationPID() const
{
    return _applicationPID;
}

QString SHMRequest::getReadableDateTime() const
{
    return _readableLocalDateTime;
}

uint32_t SHMRequest::getLocalTimestamp() const
{
    return _localTimestamp;
}

uint32_t SHMRequest::getUTCTimestamp() const
{
    return _UTCTimestamp;
}

QString SHMRequest::getApplicationName() const
{
    return _applicationName;
}

QString SHMRequest::getHostName() const
{
    return _hostName;
}

QHostAddress SHMRequest::getIPAddress() const
{
    return _IPAddress;
}
