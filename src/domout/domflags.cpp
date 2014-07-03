#include "domflags.h"

DomFlags::DomFlags(eTimeType type) : Serializable("RFlags")
{
    if(F == type) {
        domStaticElementAttributes_["b"] = "0";
        domStaticElementAttributes_["f"] = "4";
    } else {
        domStaticElementAttributes_["b"] = "4";
        domStaticElementAttributes_["f"] = "0";
    }
    domStaticElementAttributes_.insert("sMode","N");
}
