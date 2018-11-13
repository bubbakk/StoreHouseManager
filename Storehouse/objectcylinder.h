#ifndef OBJECTCYLINDER_H
#define OBJECTCYLINDER_H

#include "storeobject.h"

#include <QObject>


class objectCylinder : public storeObject
{
    Q_OBJECT
public:
    objectCylinder(QObject *parent = nullptr);


    int heightInCentimeters() const;
    void setHeightInCentimeters(int heightInCentimeters);

    int radiusInCentimeters() const;
    void setRadiusInCentimeters(int radiusInCentimeters);

private:
    int _heightInCentimeters;
    int _radiusInCentimeters;
};

#endif // OBJECTCYLINDER_H
