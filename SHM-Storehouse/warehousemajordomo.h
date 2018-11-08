#ifndef WAREHOUSEMAJORDOMO_H
#define WAREHOUSEMAJORDOMO_H

#include <QObject>
#include <QJsonValue>
#include <QJsonObject>
#include <QUuid>
#include <QLocale>
#include <QTcpSocket>

#include "../sharedcode/shmrequestparser.h"
#include "../sharedcode/shmrequest.h"
#include "../sharedcode/tcpchat.h"

#include "storeobject.h"
#include "warehouse.h"
#include "objectcylinder.h"

class warehouseMajordomo : public QObject
{
    Q_OBJECT
public:
    explicit warehouseMajordomo(QObject *parent = nullptr);
    void listenTo(tcpChat* tcpChat);
    void dispatchRequests(QList<SHMRequest*> SHMRequestsList);
    void setWareHouse(wareHouse* warehouse);

private:
    tcpChat *_tcpChat;
    wareHouse *_warehouse;
    shmRequestParser *_requestParser;
    QTcpSocket *_communicationSocket;

    storeObject* operation_CreateANewObject(QJsonValue request);
    bool operation_SetObjectLocation(QJsonValue request);
    bool operation_SetObjectStatus(QJsonValue request);

signals:

private slots:
    void parseAndDispatch(QString, QTcpSocket*);
    void commandPrintAll(void);
};

#endif // WAREHOUSEMAJORDOMO_H
