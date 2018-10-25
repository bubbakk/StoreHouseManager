#include "warehousemajordomo.h"

warehouseMajordomo::warehouseMajordomo(QObject *parent) : QObject(parent)
{
}

void warehouseMajordomo::listenTo(tcpChat *tcpChat)
{
    this->_tcpChat = tcpChat;
    this->_requestParser = new shmRequestParser(this);

    connect(this->_tcpChat, SIGNAL(messageReceived(QString, QTcpSocket*)),
            this, SLOT(parseAndDispatch(QString, QTcpSocket*)));
}

void warehouseMajordomo::parseAndDispatch(QString message, QTcpSocket* socket)
{
    this->_communicationSocket = socket;

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
    // and..... action!
    for ( int i = 0 ; i < SHMRequestsList.count() ; i++ )
    {
        QString action = SHMRequestsList[i]->_data["request"].toString();

        // ADD A NEW OBJECT
        if ( action == "add a new object")
        {
            storeObject* createdObject = this->operation_CreateANewObject(SHMRequestsList[i]->_data);
            this->_warehouse->addPackageToWareHouse(createdObject);
            QMap<QString, QString> valuesToSend;
            valuesToSend.insert("requestReferenceID", QString(SHMRequestsList[i]->_applicationPID + "-" + SHMRequestsList[i]->_UTCTimestamp));
            valuesToSend.insert("createdObjectID", createdObject->internalCode().toString());
            this->_tcpChat->sendJSONMessageToClient(this->_communicationSocket, valuesToSend);
        } else
        if  ( action == "pick")
        {

        }
        else
        {
            qWarning() << "Request " << action << " unknown";
        }
    }
}

void warehouseMajordomo::setWareHouse(wareHouse *warehouse)
{
    this->_warehouse = warehouse;
}

/*
 * Create cylinder or boxes objects
 *
 * actually filled fields are:
 *   * UUID
 */
storeObject* warehouseMajordomo::operation_CreateANewObject(QJsonValue request)
{
    QJsonObject dummyQJO;
    QJsonArray barCodesArray;
    QDateTime *computedDateTime;
    storeObject* newStoreObject = new objectCylinder();                 // instacing generates a UUID as internalCode property and creationLocalDateTime

    // check object type
    if (request["objectType"].toString() != "cylinder")                 // a cylinder
    {
        qWarning() << "object type " << request["objectType"].toString() << " unknown";
        return nullptr;
    }

    // set weight
    //newStoreObject->setWeightInGrams(request["weight"].toInt());

    // set barcodes
    if (request["barCodes"].type() != QJsonValue::Array)
    {
        qWarning() << "data object must have a \"barCodes\" array field ";
        return nullptr;
    }
    barCodesArray = request["barCodes"].toArray();
    for ( int i = 0 ; i < barCodesArray.count(); i++ )
    {
        dummyQJO = barCodesArray[i].toObject();
        storeObject::barcodeStruct *newBarCodeData = new storeObject::barcodeStruct();

        // code
        newBarCodeData->code = dummyQJO["code"].toString();
        // type
        if ( dummyQJO["type"] == "code128" )
            newBarCodeData->barcodeType = storeObject::barcodeEnum::code128;
        else
        if ( dummyQJO["type"] == "code39" )
            newBarCodeData->barcodeType = storeObject::barcodeEnum::code39;
        else
        qWarning() << "barcode type " << newBarCodeData->code << " not yet added to available types";
        newStoreObject->addBarCode(newBarCodeData);
    }

    // set arrival timestamp
    computedDateTime = new QDateTime();
    computedDateTime->setTime_t(static_cast<uint>(request["arrivalTimestamp"].toInt()));
    newStoreObject->setArrivalLocalDateTime(computedDateTime);

    // cylinder specific
    if (request["objectType"].toString() == "cylinder")                 // a cylinder
    {
        // set cylinder size
        QJsonValue sizeJsonVariant = request["size"];
        int height = sizeJsonVariant["height"].toInt();
        int radius = sizeJsonVariant["radius"].toInt();
        (static_cast<objectCylinder>(newStoreObject)).setHeightInCentimeters(height);
        (static_cast<objectCylinder>(newStoreObject)).setRadiusInCentimeters(radius);

        // now print debug values
        qDebug();
        qDebug() << "(warehouseMajordomo::operation_CreateANewObject)";
        qDebug() << "ⓘ creato oggetto cilindro:";
        qDebug() << "  internal code:            " << newStoreObject->internalCode().toString();
        qDebug() << "  creation local date/time: " << newStoreObject->arrivalLocalDateTime()->toString(Qt::DateFormat::LocalDate);
        qDebug() << "  arrival local date/time:  " << newStoreObject->creationLocalDateTime()->toString(Qt::DateFormat::LocalDate);
        qDebug() << "  height:                   " <<  (static_cast<objectCylinder>(newStoreObject)).heightInCentimeters();
        qDebug() << "  radius:                   " <<  (static_cast<objectCylinder>(newStoreObject)).radiusInCentimeters();

    }

    return newStoreObject;
}





