#include "warehousemajordomo.h"

warehouseMajordomo::warehouseMajordomo(QObject *parent) : QObject(parent)
{
}

void warehouseMajordomo::listenTo(tcpChat *tcpChat)
{
    this->_tcpChat = tcpChat;
    this->_requestParser = new shmRequestParser(this);

    connect(this->_tcpChat, SIGNAL(messageReceived(QString)),
            this, SLOT(parseAndDispatch(QString)));
}

void warehouseMajordomo::parseAndDispatch(QString message)
{
    // parse
    if ( !this->_requestParser->parse(message) )
    {
        return ;
    }

    // dispatch
    this->dispatchRequests(this->_requestParser->getSHMRequestsList());
}

void warehouseMajordomo::dispatchRequests(QList<SHMRequest *> SHMRequestsList)
{
    bool unknownRequest;

    // and..... action!
    for ( int i = 0 ; i < SHMRequestsList.count() ; i++ )
    {
        unknownRequest = true;

        QString action = SHMRequestsList[i]->_data["request"].toString();

        // ADD A NEW OBJECT
        if ( action == "add a new object")
        {
            unknownRequest = false;
            this->operation_AddANewObject(SHMRequestsList[i]->_data);
        }

        if ( unknownRequest )
        {
            qWarning() << "Request " << action << " unknown";
        }
    }
}

void warehouseMajordomo::operation_AddANewObject(QJsonValue request)
{
    QJsonObject dummyQJO;
    QJsonArray barCodesArray;
    QUuid uui;
    storeObject* newStoreObject;

    // instance a new object type
    // instacing generates a UUID
    if (request["objectType"].toString() == "cylinder")
    {
        newStoreObject = new objectCylinder();
    } else {
        qWarning() << "object type " << request["objectType"].toString() << " unknown";
        return;
    }

    // weight
    //newStoreObject->setWeightInGrams(request["weight"].toInt());

    // set barcodes
    if (request["barCodes"].type() != QJsonValue::Array)
    {
        qWarning() << "data object must have a \"barCodes\" array field ";
        return;
    }
    barCodesArray = request["objectType"].toArray();
    for ( int i = 0 ; i < barCodesArray.count(); i++ )
    {
        dummyQJO = barCodesArray[i].toObject();
        storeObject::barcodeStruct* newBarCodeValue = new storeObject::barcodeStruct();
        // code
        newBarCodeValue->code = dummyQJO["code"].toString();
        // type
        if ( newBarCodeValue->code == "code128" )
            newBarCodeValue->barcodeType = storeObject::barcodeEnum::code128;
        else
        if ( newBarCodeValue->code == "code39" )
            newBarCodeValue->barcodeType = storeObject::barcodeEnum::code39;
        else
        qWarning() << "barcode type " << newBarCodeValue->code << " not yet added to available types";
        // metadata
        //newBarCodeValue->metaData.insert("tag", dummyQJO["tag"].toString());
    }

    //


    int arrivalTimestamp = request["arrivalTimestamp"].toInt();
}




