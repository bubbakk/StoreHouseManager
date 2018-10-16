#include "warehouse.h"

wareHouse::wareHouse(int maxHorizontalSizeInMeters, int maxVerticalSizeInMeters)
{
    this->_maxHorizontalSizeInMillimeters = maxHorizontalSizeInMeters * 1000;
    this->_maxVerticalSizeInMillimeters = maxVerticalSizeInMeters * 1000;
}

