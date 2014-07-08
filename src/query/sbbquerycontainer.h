#ifndef SBBQUERYCONTAINER_H
#define SBBQUERYCONTAINER_H

#include "../util/serializable.h"

class SBBQueryContainer : public Serializable
{
public:
    SBBQueryContainer();

    virtual QDomElement toXML(QDomDocument &query);
};

#endif // SBBQUERYCONTAINER_H
