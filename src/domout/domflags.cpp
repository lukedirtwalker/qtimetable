#include "domflags.h"

DomFlags::DomFlags(eTimeType type)
{
    this->initXMLFields();
    switch(type)
    {
    case F:
        domStaticElementAttributes_["b"] = "0";
        domStaticElementAttributes_["f"] = "4";
        break;
    case B:
        domStaticElementAttributes_["b"] = "4";
        domStaticElementAttributes_["f"] = "0";
        break;
    }
}

DomFlags::DomFlags()
{
    this->initXMLFields();
}

void DomFlags::initXMLFields()
{
    domStaticElementName_ = "RFlags";
    domStaticElementAttributes_.insert("b","0");
    domStaticElementAttributes_.insert("f","4");
    domStaticElementAttributes_.insert("sMode","N");
}
