#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QObject>
#include <QString>
#include <QList>
#include <QPoint>

class wareHouse
{
public:
    wareHouse(int maxHorizontalSizeInMeters, int maxVerticalSizeInMeters);
    bool addArea(QList<QPoint> perimeter, QString name, QString color = "");
    void addObject();

    // area data structure inside the storehouse
    struct areaStruct
    {
        QString name;
        QList<QPoint> perimeter;
        QString cssColor;
        QString code;
    };
    QList<areaStruct> areas;

private:
    int _maxHorizontalSizeInMillimeters;
    int _maxVerticalSizeInMillimeters;

    struct objectBox
    {
        int sizeXInMillimeters;
        int sizeYInMillimeters;
        int sizeZInMillimeters;
        int weightInGrams;

    };

    struct objectCylinder
    {
        int radiusInMillimeters;
        int heightInMillimeters;

    };
};

#endif // WAREHOUSE_H
