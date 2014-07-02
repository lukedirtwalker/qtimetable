#ifndef DOMSTATION_H
#define DOMSTATION_H

#include "../util/serializable.h"

class DomStation : public Serializable
{
public:
    DomStation();
    DomStation(QString name, QString id);

private:
    void initXMLFields();
};

#endif // DOMSTATION_H
