#ifndef STOREOBJECT_H
#define STOREOBJECT_H

#include "warehouse.h"
#include <QObject>
#include <QImage>
#include <QList>
#include <QMap>
#include <QDateTime>
#include <QUuid>

class storeObject : public QObject
{
    Q_OBJECT
public:

    enum barcodeEnum {code128, code39, QRCode, SCC, EAN, ISBN, UCC};

    explicit storeObject(QObject *parent = nullptr);

    void addBarCode(barcodeEnum barcodeType, QString code);

signals:

public slots:

private:

    // barcode data structure
    struct barcodeStruct
    {
        barcodeEnum barcodeType;
        QString content;
        QMap<QString, QString> metaData;
    };

    QUuid* _internalCode;                                   // codice univoco generato
    int _weightInGrams;                                     // serve il peso ?
    QImage _barcode;                                        // serve l'immagine rilevata ?
    QList<barcodeStruct*> barcodes;                         // uno o più barcode?
    QMap<QString, QString> codes;
    QDateTime* _arrivalLocalDateTime;                       // data e ora di arrivo (creazione) dell'oggetto
    QDateTime* _creationLocalDateTime;                      // data e ora di creazione dell'oggetto

    QMap<QDateTime*, QPoint*> staticLocationsHistory;                   // lo storico delle movimentazioni "da fermo"
    QMap<QDateTime*, QPoint*> movementHistory;                          // lo storico delle posizioni, rilevate puntualmente
    QMap<QDateTime*, wareHouse::areaStruct*> areaLocationsHistory;      // lista di puntatore di aree in cui l'oggetto è stato
    wareHouse::areaStruct* actualAreaLocation;                          // puntatore all'area in cui l'oggetto si trova attualmente


};

#endif // STOREOBJECT_H
