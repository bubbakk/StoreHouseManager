#include "warehousemajordomo.h"

warehouseMajordomo::warehouseMajordomo(QObject *parent) : QObject(parent)
{
}

/*
 * Collega l'evento messageReceived della chat TCP con il parser della richiesta
 *
 */
void warehouseMajordomo::listenTo(tcpChat *tcpChat)
{
    this->_tcpChat = tcpChat;
    this->_requestParser = new shmRequestParser(this);

    connect(this->_tcpChat, SIGNAL(messageReceived(QString, QTcpSocket*)),
            this, SLOT(parseAndDispatch(QString, QTcpSocket*)));
    connect(this->_tcpChat, SIGNAL(printAllRequest(void)),
            this, SLOT(commandPrintAll(void)));

}

/*
 * Richiama il parser per estrarre la lista delle richieste contenute nel
 * messaggio e, se andato a buon fine, invoca l'esecuzione
 *
 */
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

void warehouseMajordomo::commandPrintAll()
{
    // print all objects in the warehouse
    QHash<QString, storeObject*> _packages = this->_warehouse->packages();
    QStringList codes = _packages.keys();
    int objectsInTheWarehouse = _packages.keys().count();

    if ( objectsInTheWarehouse == 0 )
    {
        qInfo();
        qInfo() << "no object in the warehouse now";
        return;
    }

    for (int i = 0 ; i < objectsInTheWarehouse ; i++)
    {
        storeObject* object = _packages.value(codes[i]);
        qInfo();
        qInfo() << "barcode: " << object->uniqueBarcode();
        qInfo() << "status:  " << object->statusString();
        qInfo() << "entered: " << object->creationLocalDateTime();
        qInfo() << "position:";
        qInfo() << "   X: " << object->position()->locationX;
        qInfo() << "   Y: " << object->position()->locationY;
        qInfo() << "   Z: " << object->position()->locationZ;
    }
}

/*
 * Esegue tutte le richieste codificate e contenute nella lista
 *
 */
void warehouseMajordomo::dispatchRequests(QList<SHMRequest *> SHMRequestsList)
{
    QMap<QString, QString> replyToSend;

    // and..... action!
    for ( int i = 0 ; i < SHMRequestsList.count() ; i++ )
    {
        QString action = SHMRequestsList[i]->_data["request"].toString();       // the action
        QJsonValue requestData = SHMRequestsList[i]->_data;                     // the request

        // ADD A NEW OBJECT
        if ( action == "add a new object")
        {
            storeObject* createdObject = this->operation_CreateANewObject(requestData);

            if ( createdObject == nullptr )
            {
                replyToSend.insert("success", "false");         // unsuccessful operation

                qDebug();
                qDebug() << "(warehouseMajordomo::" << Q_FUNC_INFO << ")";
                qDebug() << "can't create a new object due to request format error";
            } else
            {
                this->_warehouse->addPackage(createdObject);    // add created object to warehose

                replyToSend.insert("success", "true");          // successful operation

                qInfo();
                qInfo() << "(warehouseMajordomo::" << Q_FUNC_INFO << ")";
                qInfo() << "new object successfully created and added to warehouse";
            }
        } else
        // SET LOCATION
        if ( action == "set object location")
        {
            bool success = this->operation_SetObjectLocation(requestData);

            if ( !success )
            {
                replyToSend.insert("success", "false");         // unsuccessful operation

                qDebug();
                qDebug() << "(warehouseMajordomo::" << Q_FUNC_INFO << ")";
                qDebug() << "can't set object location";
            } else
            {
                replyToSend.insert("success", "true");          // successful operation

                qInfo();
                qInfo() << "(warehouseMajordomo::" << Q_FUNC_INFO << ")";
                qInfo() << "object successfully placed in the warehouse";
            }
        } else
        if ( action.length() > 14 && action.left(14) == "set object as ")
        {
            bool success = this->operation_SetObjectStatus(requestData);

            if ( !success )
            {
                replyToSend.insert("success", "false");         // unsuccessful operation

                qDebug();
                qDebug() << "(warehouseMajordomo::" << Q_FUNC_INFO << ")";
                qDebug() << "can't set object location";
            } else
            {
                replyToSend.insert("success", "true");          // successful operation

                qInfo();
                qInfo() << "(warehouseMajordomo::" << Q_FUNC_INFO << ")";
                qInfo() << "object successfully placed in the warehouse";
            }
        }
        else
        {
            qWarning() << "Request " << action << " unknown";
        }

        replyToSend.insert("requestReferenceID",
                           QString(SHMRequestsList[i]->_applicationPID) +
                           "-" +
                           QString(SHMRequestsList[i]->_UTCTimestamp) +
                           "." +
                           QString::number(i));
        this->_tcpChat->sendJSONMessageToClient(this->_communicationSocket, replyToSend);
    }
}

void warehouseMajordomo::setWareHouse(wareHouse *warehouse)
{
    this->_warehouse = warehouse;
}

/*!
    \fn warehouseMajordomo::operation_CreateANewObject(QJsonValue request)

    The \a request contains new object data.
    A cylinder or a box object is created and its pointer returned.
    If the operation is unsuccessfull \c nullptr is returned.
*/
storeObject* warehouseMajordomo::operation_CreateANewObject(QJsonValue request)
{
    QJsonObject dummyQJO;
    QJsonArray barCodesArray;
    //QDateTime *computedDateTime;
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

        // the first barcode is the object unique identiy code
        if ( i == 0 ) {
            newStoreObject->setUniqueBarcode(newBarCodeData->code);
        }
    }

    // set arrival timestamp
    //computedDateTime = new QDateTime();
    //computedDateTime->setTime_t(static_cast<uint>(request["arrivalTimestamp"].toInt()));
    //newStoreObject->setArrivalLocalDateTime(computedDateTime);

    // cylinder specific
    if (request["objectType"].toString() == "cylinder")                 // a cylinder
    {
        // set cylinder size
        //QJsonValue sizeJsonVariant = request["size"];
        //int height = sizeJsonVariant["height"].toInt();
        //int radius = sizeJsonVariant["radius"].toInt();
        //(static_cast<objectCylinder>(newStoreObject)).setHeightInCentimeters(height);
        //(static_cast<objectCylinder>(newStoreObject)).setRadiusInCentimeters(radius);

        // now print debug values
        qDebug();
        qDebug() << "(warehouseMajordomo::" << Q_FUNC_INFO << ")";
        qDebug() << "ⓘ creato oggetto cilindro:";
        qDebug() << "  internal code:            " << newStoreObject->internalCode().toString();
        qDebug() << "  unique barcode:           " << newStoreObject->uniqueBarcode();
        qDebug() << "  creation local date/time: " << newStoreObject->creationLocalDateTime()->toString(Qt::DateFormat::LocalDate);
        //qDebug() << "  arrival local date/time:  " << newStoreObject->arrivalLocalDateTime()->toString(Qt::DateFormat::LocalDate);
        //qDebug() << "  height:                   " <<  (static_cast<objectCylinder>(newStoreObject)).heightInCentimeters();
        //qDebug() << "  radius:                   " <<  (static_cast<objectCylinder>(newStoreObject)).radiusInCentimeters();
    }

    return newStoreObject;
}

/*!
    \fn warehouseMajordomo::operation_SetObjectLocation(QJsonValue request)

    The \a request contains object barcode and new location cooordinates.
    If the new location can be set \c true is returned, otherwise \c false.
*/
bool warehouseMajordomo::operation_SetObjectLocation(QJsonValue request)
{
    QString barcode = request["barcode"].toString();
    QJsonObject dummyQJO = request["location"].toObject();
    int x = dummyQJO["X"].toInt();
    int y = dummyQJO["Y"].toInt();
    int z = dummyQJO["Z"].toInt();

    if ( !this->_warehouse->placePackage(barcode, x, y, z) )                    // set new location
    {
        qWarning();
        qWarning() << "(warehouseMajordomo::" << Q_FUNC_INFO << ")";
        qWarning() << "object not found in the warehouse";

        return false;
    }

    return true;
}

bool warehouseMajordomo::operation_SetObjectStatus(QJsonValue request)
{
    QString barcode = request["barcode"].toString();
    QJsonObject dummyQJO = request["location"].toObject();
    QString action = (request["request"].toString()).mid(14);
    bool success = false;

    if ( action == "moving" ) {
        success = this->_warehouse->setPackageAsMoving(barcode);
    } else
    if ( action == "static" ) {
        success = this->_warehouse->setPackageAsStatic(barcode);
    } else
    if ( action == "processing" ) {
        success = this->_warehouse->setPackageAsUnderProcessing(barcode);
    } else
    if ( action == "processed" ) {
        success = this->_warehouse->setPackageAsProcessed(barcode);
    } else
    {
        qWarning();
        qWarning() << "(warehouseMajordomo::" << Q_FUNC_INFO << ")";
        qWarning() << "status " << action << " unknown";
    }

    return success;
}





