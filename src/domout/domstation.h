#ifndef DOMSTATION_H
#define DOMSTATION_H

#include "../util/serializable.h"

class DomStation : public Serializable
{
public:
    DomStation(QString name, QString id);

};

#endif // DOMSTATION_H
