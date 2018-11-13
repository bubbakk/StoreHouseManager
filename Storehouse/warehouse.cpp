#include "warehouse.h"

wareHouse::wareHouse(int maxHorizontalSizeInMeters, int maxVerticalSizeInMeters)
{
    this->_maxHorizontalSizeInCentimeters = maxHorizontalSizeInMeters * 100;
    this->_maxVerticalSizeInCentimeters = maxVerticalSizeInMeters * 100;
}

/*
 * Ritorna true se l'oggetto è (oppure era) presente nel magazzino,
 * false altrimenti
 *
 */
bool wareHouse::isPackagePresent(QString code)
{
    return this->_packages.contains(code);
}

/*
 * Aggiunge un oggetto al magazzino e ritorna true
 * Se l'oggetto è (oppure era) già presente ritorna false
 *
 */
bool wareHouse::addPackage(storeObject *package)
{
    QString packageBarCode = package->uniqueBarcode();

    if ( this->isPackagePresent(packageBarCode) ) {
        return false;
    }

    this->_packages[packageBarCode] = package;      // add object to warehouse hash

    qInfo();
    qDebug() << "(wareHouse::addPackageToWareHouse)";
    qInfo() << "Just added a new object in the warehouse";
    qInfo() << "Actual packages in the warehouse: " << this->_packages.count();

    return true;
}

bool wareHouse::placePackage(QString code, int x, int y, int z)
{
    if ( !this->isPackagePresent(code) ) {
        return false;
    }

    // imposta la posizione dell'oggetto
    storeObject* object = this->_packages[code];
    object->setPosition(x, y, z);

    return true;
}

/*
 * Imposta lo stato dell'oggetto a "in movimentazione" e ritorna true.
 * Ritorna false se l'oggetto con il codice non è in magazzino
 *
 */
bool wareHouse::setPackageAsMoving(QString code)
{
    return setPackageStatus(code, storeObject::is_moving);
}

/*
 * Imposta lo stato dell'oggetto a "in lavorazione" e ritorna true.
 * Ritorna false se l'oggetto con il codice non è in magazzino
 *
 */
bool wareHouse::setPackageAsUnderProcessing(QString code)
{
    return setPackageStatus(code, storeObject::is_processing);
}

/*
 * Imposta lo stato dell'oggetto a "completamente lavorato" e ritorna true.
 * Ritorna false se l'oggetto con il codice non è in magazzino
 *
 */
bool wareHouse::setPackageAsProcessed(QString code)
{
    return setPackageStatus(code, storeObject::is_processed);
}

/*
 * Imposta lo stato dell'oggetto a "statico" e ritorna true.
 * Ritorna false se l'oggetto con il codice non è in magazzino
 *
 */
bool wareHouse::setPackageAsStatic(QString code)
{
    return setPackageStatus(code, storeObject::is_static);
}

QHash<QString, storeObject *> wareHouse::packages() const
{
    return _packages;
}

bool wareHouse::setPackageStatus(QString code, storeObject::statusEnum status)
{
    if ( !this->isPackagePresent(code) ) {
        return false;
    }

    storeObject *package = this->_packages[code];
    package->setStatus(status);

    return true;
}

/*
 * Salva i dati in un database SQLite
 */
bool wareHouse::saveData()
{
    return true;
}

/*
 * Carica i dati da un database SQLite
 */
bool wareHouse::loadData()
{
    return true;
}

/*
 * Verifica la presenza del file SQLite e, se assente, crea il database
 */
bool wareHouse::initDatabase()
{
    return true;
}
