#include "storeobject.h"

storeObject::storeObject(QObject *parent) : QObject(parent)
{
    this->_internalCode = new QUuid();
}

void storeObject::addBarCode(storeObject::barcodeEnum barcodeType, QString code)
{
    barcodeStruct* barcode = new barcodeStruct();

    barcode->barcodeType = barcodeType;
    barcode->content = code;

    this->barcodes.append(barcode);
}
