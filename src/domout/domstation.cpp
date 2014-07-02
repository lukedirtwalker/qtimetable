#include "domstation.h"

DomStation::DomStation()
{
    this->initXMLFields();
}

DomStation::DomStation(QString name, QString id)
{
    initXMLFields();
    domStaticElementAttributes_["name"] = name;
    domStaticElementAttributes_["externalId"] = id;
}

void DomStation::initXMLFields()
{
    domStaticElementName_ = "Station";
    domStaticElementAttributes_.insert("name","");
    domStaticElementAttributes_.insert("externalId","");
}
