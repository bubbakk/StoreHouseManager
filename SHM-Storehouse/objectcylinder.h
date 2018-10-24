#ifndef OBJECTCYLINDER_H
#define OBJECTCYLINDER_H

#include "storeobject.h"

#include <QObject>


class objectCylinder : public storeObject
{
    Q_OBJECT
public:
    objectCylinder(QObject *parent = nullptr);


private:
    int _heightInMillimeters;
    int _radiusInMillimeters;
};

#endif // OBJECTCYLINDER_H
