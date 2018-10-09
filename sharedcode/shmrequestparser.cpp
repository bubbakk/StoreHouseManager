#include "shmrequestparser.h"

shmRequestParser::shmRequestParser(QObject *parent) : QObject(parent)
{

}

bool shmRequestParser::parse(QString messageToParse)
{
    QJsonArray result;
    QJsonParseError error;
    QJsonArray requestsArray;
    QString firstMissingField = "";
    SHMRequest* shmRequest;
    QJsonObject dummyQJO;

    this->SHMRequestsList.clear();                                             // svuota la lista richieste

    // parse JSON string
    QJsonDocument jsonDoc = QJsonDocument::fromJson(messageToParse.toUtf8(), &error);
    if ( jsonDoc.isNull() ) {                                                   // verify parsing error
        this->errorMessage = "JSON message parsing error: " + error.errorString();     // set error string
        qWarning().noquote() << this->errorMessage;                                    // log JSON formato error
        return false;                                                           // return unsuccess
    }

    // check if there is an array; if not return error
    if ( !jsonDoc.isArray() ) {
        this->errorMessage = "JSON message format error: the first level must be an array";
        qWarning().noquote() << this->errorMessage;
        return false;
    }

    // ready to parse array
    requestsArray = jsonDoc.array();

    // check if there is no content at all (empty array)
    if ( requestsArray.isEmpty() ) {
        this->errorMessage = "JSON message without content: the array must not be empty";
        qWarning().noquote() << this->errorMessage;
        return false;
    }

    // verify all requests in the array
    // all of them must be good; if not, the entire array of requests can be compromized
    for ( int i = 0 ; i < requestsArray.count() ; i++ ) {
        dummyQJO = requestsArray[i].toObject();
        if ( !this->messageFormatCheck(&dummyQJO, &firstMissingField) ) {
            this->errorMessage = "JSON message " + QString::number(i) + " format error: missing field(s) " + firstMissingField;
            qCritical().noquote() << this->errorMessage;
            return false;
        }
    }

    // extract requests in the array, one by one, and create the list
    for ( int i = 0 ; i < requestsArray.count() ; i++ ) {
        dummyQJO = requestsArray[i].toObject();
        if ( !this->messageFormatCheck(&dummyQJO, &firstMissingField) ) {
            this->errorMessage = "JSON message " + QString::number(i) + " format error: missing field(s) " + firstMissingField;
            qCritical().noquote() << this->errorMessage;
            return false;
        }
    }

    // all messages are ok: create SHM messages list
    for ( int i = 0 ; i < requestsArray.count() ; i++ ) {
        dummyQJO = requestsArray[i].toObject();
        shmRequest = new SHMRequest();

        this->extractSHMRequest(&dummyQJO, shmRequest);         // do the work!
        this->SHMRequestsList.append(shmRequest);

    }

    return true;
}

bool shmRequestParser::messageFormatCheck(QJsonObject* JSONObjectToCheck, QString* missingFields)
{
    QJsonObject requestObject;
    QJsonValue dummyQJV;
    QStringList missingFieldsList;
    bool result = true;

    missingFields->clear();

    // field "hostRequestData" container must be present
    if ( JSONObjectToCheck->value("hostRequestData") == QJsonValue::Undefined ) {
        missingFields->append("hostRequestData");
        return false;
    }

    requestObject = JSONObjectToCheck->value("hostRequestData").toObject();

    for (int i = 0; i < this->mandatoryFields.size(); ++i) {
        dummyQJV = requestObject.value(mandatoryFields[i]);
        if ( dummyQJV.isUndefined() ) {
            missingFieldsList.append(mandatoryFields[i]);
            result = false;
        }
    }

    missingFields->append(missingFieldsList.join(" "));

    return result;
}

void shmRequestParser::extractSHMRequest(QJsonObject* JSONObjectSource, SHMRequest* request)
{
    QJsonObject requestObject;
    QJsonValue dummyQJV;
    QStringList missingFieldsList;

    requestObject = JSONObjectSource->value("hostRequestData").toObject();

    request->setRequest(requestObject.value("IPAddress").toString(),
                        requestObject.value("hostName").toString(),
                        requestObject.value("applicationName").toString(),
                        requestObject.value("applicationPID").toString(),
                        requestObject.value("UTCTimestamp").toString(),
                        requestObject.value("localTimestamp").toString(),
                        requestObject.value("readableDateTime").toString(),
                        requestObject.value("messageType").toString()
                        );
}
