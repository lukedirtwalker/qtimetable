#ifndef LOCATION_H
#define LOCATION_H

#include "../util/globalshared.h"

#include <QString>

class Location
{
public:
    Location() : type_{UNDEFINED} {}
    Location(eLocationType t) : type_(t) {}

    inline QString getName();
    inline eLocationType getType();

protected:
    QString name_;
    eLocationType type_;
};

inline QString Location::getName() { return name_;}

inline eLocationType Location::getType() { return type_;}

#endif // LOCATION_H
