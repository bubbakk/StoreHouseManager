#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QObject>
#include <QString>
#include <QPoint>
#include <QPolygon>
#include <QDebug>

#include "storeobject.h"

#define SQLITE_FILENAME "./warehouse.sqlite"

class wareHouse
{
public:
    wareHouse(int maxHorizontalSizeInMeters, int maxVerticalSizeInMeters);
    //bool addArea(QList<QPoint> perimeter, QString name, QString color = "");

    bool isPackagePresent(QString code);                // verifica se il barcode è presente in magazzino
    bool addPackage(storeObject *package);              // aggiunge un nuovo oggetto al magazzino
    bool placePackage(QString code, int x, int y, int z);                    // TODO: posiziona un oggetto
    bool setPackageAsMoving(QString code);              // imposta oggetto come "in movimento"
    bool setPackageAsUnderProcessing(QString code);     // imposta oggetto come "in lavorazione"
    bool setPackageAsProcessed(QString code);           // imposta oggetto come "lavorato" (non tornerà più in magazzino)
    bool setPackageAsStatic(QString code);              // imposta oggetto come "posizionato in magazzino"


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

    QHash<QString, storeObject *> packages() const;

private:
    int _maxHorizontalSizeInCentimeters;
    int _maxVerticalSizeInCentimeters;

    QHash<QString, storeObject*> _packages;

    bool setPackageStatus(QString code, storeObject::statusEnum status);    // imposta uno degli stati possibili per l'oggetto

    bool saveData();
    bool loadData();
    bool initDatabase();
};

#endif // WAREHOUSE_H
