#ifndef STOREOBJECT_H
#define STOREOBJECT_H

#include <QObject>
#include <QImage>
#include <QList>
#include <QMap>
#include <QDateTime>
#include <QUuid>
#include <QPoint>

class storeObject : public QObject
{
    Q_OBJECT
public:

    enum barcodeEnum {code128, code39, QRCode, SCC, EAN, ISBN, UCC};
    Q_ENUM(barcodeEnum)
    enum statusEnum {
        is_static,              // si trova in un'area del magazzino
        is_moving,              // è attualmente movimentato da un carrellista
        is_processing,          // è in fase di lavorazione
        is_processed            // è completamente lavorato: da eliminare dal magazzino
    };
    Q_ENUM(statusEnum)

    // barcode data structure
    struct barcodeStruct
    {
        barcodeEnum barcodeType;
        QString code;
        QMap<QString, QString> metaData;
    };

    // position data structure
    struct positionStruct
    {
        int locationX;
        int locationY;
        int locationZ;
    };

    explicit storeObject(QObject *parent = nullptr);

    void addBarCode(barcodeEnum barcodeType, QString code);
    void addBarCode(barcodeStruct *barCodeData);

    QUuid internalCode() const;
    void setInternalCode(const QUuid &internalCode);

    QDateTime *arrivalLocalDateTime() const;
    void setArrivalLocalDateTime(QDateTime *arrivalLocalDateTime);

    QDateTime *creationLocalDateTime() const;
    void setCreationLocalDateTime(QDateTime *creationLocalDateTime);

    QString uniqueBarcode() const;
    void setUniqueBarcode(const QString &uniqueBarcode);

    statusEnum status() const;
    QString statusString();
    void setStatus(const statusEnum &status);

    positionStruct* position() const;
    void setPosition(int x, int y, int z);

signals:

public slots:

private:

    QUuid _internalCode;                                // codice univoco generato
    QString _uniqueBarcode;                             // barcode univoco del prodotto
    //int _weightInGrams;                                 // serve il peso ?
    //QImage _barcode;                                    // serve l'immagine rilevata ?
    QList<barcodeStruct *> _barcodes;                   // uno o più barcode?
    QDateTime *_arrivalLocalDateTime;                   // data e ora di arrivo (creazione) dell'oggetto
    QDateTime *_creationLocalDateTime;                  // data e ora di creazione dell'oggetto
    //int _actualAreaLocation;                            // puntatore all'area in cui l'oggetto si trova attualmente
    statusEnum _status;                                 // stato dell'oggetto
    positionStruct* _position = new positionStruct;     // posizione corrente (se lo stato dell'oggetto è _status=is_static)
    //QString _lastForkliftMoving;                        // codice del carrello che sta attualmente movimentando l'oggetto o se _isMoving vale TRUE,
                                                          // altrimenti indica l'ultimo che l'ha movimentato

    QMap<QDateTime *, QPoint *> _staticLocationsHistory;    // lo storico delle posizioni (oggetto depositato)
    //QMap<QDateTime *, QPoint *> _movementHistory;           // lo storico delle posizioni, rilevate puntualmente
    //QMap<QDateTime *, int> _areaLocationsHistory;           // lista di puntatore di aree in cui l'oggetto è stato

};

#endif // STOREOBJECT_H
