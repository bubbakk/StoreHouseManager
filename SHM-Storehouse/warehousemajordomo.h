#ifndef WAREHOUSEMAJORDOMO_H
#define WAREHOUSEMAJORDOMO_H

#include <QObject>
#include <QJsonValue>
#include <QJsonObject>
#include <QUuid>

#include "../sharedcode/shmrequestparser.h"
#include "../sharedcode/shmrequest.h"
#include "../sharedcode/tcpchat.h"

#include "storeobject.h"
#include "objectcylinder.h"

class warehouseMajordomo : public QObject
{
    Q_OBJECT
public:
    explicit warehouseMajordomo(QObject *parent = nullptr);
    void listenTo(tcpChat* tcpChat);
    void dispatchRequests(QList<SHMRequest*> SHMRequestsList);

private:
    tcpChat* _tcpChat;
    shmRequestParser* _requestParser;

    void operation_AddANewObject(QJsonValue request);

signals:

private slots:
    void parseAndDispatch(QString);
};

#endif // WAREHOUSEMAJORDOMO_H
