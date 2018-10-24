#include "storeobject.h"


storeObject::storeObject(QObject *parent) : QObject(parent)
{
    // when instancing a new object, a new UUID is created
    this->_internalCode = QUuid::createUuid();
}

void storeObject::addBarCode(storeObject::barcodeEnum barcodeType, QString code)
{
    barcodeStruct* barcode = new barcodeStruct();

    barcode->barcodeType = barcodeType;
    barcode->code = code;

    this->_barcodes.append(barcode);
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

