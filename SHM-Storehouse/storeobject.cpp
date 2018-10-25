#include "storeobject.h"


storeObject::storeObject(QObject *parent) : QObject(parent)
{
    // when instancing a new object:

    // a new UUID is created
    this->_internalCode = QUuid::createUuid();
    // a DateTime creation is assigned
    this->_creationLocalDateTime = new QDateTime(QDateTime::currentDateTime());
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

int storeObject::weightInGrams() const
{
    return _weightInGrams;
}

void storeObject::setWeightInGrams(int weightInGrams)
{
    _weightInGrams = weightInGrams;
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


