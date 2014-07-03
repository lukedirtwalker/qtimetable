#ifndef LOCATION_H
#define LOCATION_H

#include "../util/globalshared.h"

#include <QString>

class Location
{
public:
    Location();

    QString getName();
    eLocationType getType();

protected:
    QString mName;
    eLocationType mType;
};

#endif // LOCATION_H
