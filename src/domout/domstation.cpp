#include "domstation.h"

DomStation::DomStation(QString name, QString id) : Serializable("Station")
{
    domStaticElementAttributes_["name"] = name;
    domStaticElementAttributes_["externalId"] = id;
}
