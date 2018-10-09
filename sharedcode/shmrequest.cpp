#include "shmrequest.h"

SHMRequest::SHMRequest()
{

}

void SHMRequest::setRequest(QString IPAddress,
                            QString hostName,
                            QString applicationName,
                            QString applicationPID,
                            QString UTCTimestamp,
                            QString localTimestamp,
                            QString readableDateTime,
                            QString messageType)
{
    qInfo().noquote() << "◌ Implementare controlli sull'assegnazione in SHMRequest::setRequest()";

    this->IPAddress.setAddress(IPAddress);                                                          // conversion to QHostAddress
    this->hostName = hostName;
    this->applicationName = applicationName;
    this->applicationPID = applicationPID.toUShort();                                               // conversion to uint16_t
    this->UTCTimestamp = UTCTimestamp.toUShort();                                                   // conversion to uint32_t
    this->localTimestamp = localTimestamp.toUShort();                                               // conversion to uint32_t
    this->readableDateTime = readableDateTime;
    this->messageType = static_cast<messageTypeEnum>(dummyQME.keyToValue(messageType.toLatin1()));  // conversion to enum
}

uint16_t SHMRequest::getApplicationPID() const
{
    return applicationPID;
}

QString SHMRequest::getReadableDateTime() const
{
    return readableDateTime;
}

uint32_t SHMRequest::getLocalTimestamp() const
{
    return localTimestamp;
}

uint32_t SHMRequest::getUTCTimestamp() const
{
    return UTCTimestamp;
}

QString SHMRequest::getApplicationName() const
{
    return applicationName;
}

QString SHMRequest::getHostName() const
{
    return hostName;
}

QHostAddress SHMRequest::getIPAddress() const
{
    return IPAddress;
}
