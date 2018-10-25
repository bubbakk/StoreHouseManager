#include "objectcylinder.h"

objectCylinder::objectCylinder(QObject *parent) : storeObject(parent)
{

}

int objectCylinder::heightInCentimeters() const
{
    return _heightInCentimeters;
}

void objectCylinder::setHeightInCentimeters(int heightInCentimeters)
{
    _heightInCentimeters = heightInCentimeters;
}

int objectCylinder::radiusInCentimeters() const
{
    return _radiusInCentimeters;
}

void objectCylinder::setRadiusInCentimeters(int radiusInCentimeters)
{
    _radiusInCentimeters = radiusInCentimeters;
}
