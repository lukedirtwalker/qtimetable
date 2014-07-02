#include "domaddress.h"

DomAddress::DomAddress(QString name, QString latitude, QString longitude)
{
    initXMLFields();
    domStaticElementAttributes_["name"] = name;
    domStaticElementAttributes_["x"] = longitude;
    domStaticElementAttributes_["y"] = latitude;
}

void DomAddress::initXMLFields()
{
    domStaticElementName_ = "Address";
    domStaticElementAttributes_.insert("name","");
    domStaticElementAttributes_.insert("x","");
    domStaticElementAttributes_.insert("y","");
}
