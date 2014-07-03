#include "domaddress.h"

DomAddress::DomAddress(QString name, QString latitude, QString longitude)
    : Serializable("Address")
{
    domStaticElementAttributes_["name"] = name;
    domStaticElementAttributes_["x"] = longitude;
    domStaticElementAttributes_["y"] = latitude;
}
