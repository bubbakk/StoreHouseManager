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

    // barcode data structure
    struct barcodeStruct
    {
        barcodeEnum barcodeType;
        QString code;
        QMap<QString, QString> metaData;
    };

    explicit storeObject(QObject *parent = nullptr);

    void addBarCode(barcodeEnum barcodeType, QString code);

    int weightInGrams() const;
    void setWeightInGrams(int weightInGrams);

    QUuid internalCode() const;
    void setInternalCode(const QUuid &internalCode);

signals:

public slots:

private:

    QUuid _internalCode;                                   // codice univoco generato
    int _weightInGrams;                                     // serve il peso ?
    QImage _barcode;                                        // serve l'immagine rilevata ?
    QList<barcodeStruct*> _barcodes;                         // uno o più barcode?
    QMap<QString, QString> _codes;
    QDateTime* _arrivalLocalDateTime;                       // data e ora di arrivo (creazione) dell'oggetto
    QDateTime* _creationLocalDateTime;                      // data e ora di creazione dell'oggetto

    QMap<QDateTime*, QPoint*> _staticLocationsHistory;                   // lo storico delle movimentazioni "da fermo"
    QMap<QDateTime*, QPoint*> _movementHistory;                          // lo storico delle posizioni, rilevate puntualmente
    QMap<QDateTime*, wareHouse::areaStruct*> _areaLocationsHistory;      // lista di puntatore di aree in cui l'oggetto è stato
    wareHouse::areaStruct* _actualAreaLocation;                          // puntatore all'area in cui l'oggetto si trova attualmente
};

#endif // STOREOBJECT_H
