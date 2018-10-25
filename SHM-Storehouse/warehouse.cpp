#include "warehouse.h"

wareHouse::wareHouse(int maxHorizontalSizeInMeters, int maxVerticalSizeInMeters)
{
    this->_maxHorizontalSizeInCentimeters = maxHorizontalSizeInMeters * 100;
    this->_maxVerticalSizeInCentimeters = maxVerticalSizeInMeters * 100;
}

void wareHouse::addPackageToWareHouse(storeObject *package)
{
    this->_packages.append(package);

    qInfo();
    qDebug() << "(wareHouse::addPackageToWareHouse)";
    qInfo() << "Just added a new object in the warehouse";
    qInfo() << "Actual packages in the warehouse: " << this->_packages.count();
}

