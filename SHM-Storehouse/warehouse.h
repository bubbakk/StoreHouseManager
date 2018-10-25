#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QObject>
#include <QString>
#include <QList>
#include <QPoint>
#include <QPolygon>
#include <QDebug>

#include "storeobject.h"

class wareHouse
{
public:
    wareHouse(int maxHorizontalSizeInMeters, int maxVerticalSizeInMeters);
    bool addArea(QList<QPoint> perimeter, QString name, QString color = "");
    void addObject();

    void addPackageToWareHouse(storeObject *package);

    // area data structure inside the storehouse
    struct areaStruct
    {
        int id;
        QString name;
        QList<QPoint> perimeter;
        QString cssColor;
        QPolygon perimetralPoints;
    };
    QList<areaStruct> areas;

private:
    int _maxHorizontalSizeInCentimeters;
    int _maxVerticalSizeInCentimeters;

    QList<storeObject*> _packages;
};

#endif // WAREHOUSE_H
