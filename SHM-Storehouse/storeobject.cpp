#include "storeobject.h"


storeObject::storeObject(QObject *parent) : QObject(parent)
{
    // when instancing a new object:

    // a new UUID is created
    this->_internalCode = QUuid::createUuid();
    // a DateTime creation is assigned
    this->_creationLocalDateTime = new QDateTime(QDateTime::currentDateTime());
    // object created is set as static
    this->_status = statusEnum::is_static;
}

void storeObject::addBarCode(storeObject::barcodeEnum barcodeType, QString code)
{
    barcodeStruct* barcode = new barcodeStruct();

    barcode->barcodeType = barcodeType;
    barcode->code = code;

    this->_barcodes.append(barcode);
}

void storeObject::addBarCode(storeObject::barcodeStruct *barCodeData)
{
    this->_barcodes.append(barCodeData);
}


QUuid storeObject::internalCode() const
{
    return _internalCode;
}

void storeObject::setInternalCode(const QUuid &internalCode)
{
    _internalCode = internalCode;
}

QDateTime *storeObject::arrivalLocalDateTime() const
{
    return _arrivalLocalDateTime;
}

void storeObject::setArrivalLocalDateTime(QDateTime *arrivalLocalDateTime)
{
    _arrivalLocalDateTime = arrivalLocalDateTime;
}

QDateTime *storeObject::creationLocalDateTime() const
{
    return _creationLocalDateTime;
}

void storeObject::setCreationLocalDateTime(QDateTime *creationLocalDateTime)
{
    _creationLocalDateTime = creationLocalDateTime;
}

QString storeObject::uniqueBarcode() const
{
    return _uniqueBarcode;
}

storeObject::statusEnum storeObject::status() const
{
    return _status;
}

void storeObject::setStatus(const statusEnum &status)
{
    _status = status;
}

storeObject::positionStruct* storeObject::position() const
{
    return this->_position;
}

void storeObject::setPosition(int x, int y, int z)
{
    this->_position->locationX = x;
    this->_position->locationY = y;
    this->_position->locationZ = z;
}

void storeObject::setUniqueBarcode(const QString &uniqueBarcode)
{
    _uniqueBarcode = uniqueBarcode;
}


