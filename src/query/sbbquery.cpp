#include "sbbquery.h"

QDomDocument SBBQuery::toXML()
{
    clear();
    appendChild(queryContainer_.toXML(*this));
    return *this;
}
