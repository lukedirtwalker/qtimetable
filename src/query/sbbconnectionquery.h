#ifndef SBBCONNECTIONQUERY_H
#define SBBCONNECTIONQUERY_H

#include "sbbquery.h"
#include "../util/serializable.h"

class SBBConnectionQuery : public SBBQuery
{
public:
    SBBConnectionQuery();
    virtual ~SBBConnectionQuery();

    SBBConnectionQuery(Serializable *start, Serializable *dest, Serializable *date, Serializable *flags);
    SBBConnectionQuery(Serializable *start, Serializable *dest, Serializable *via, Serializable *date, Serializable *flags);

    virtual QDomDocument toXML();

private:
    virtual void initXMLFields();
    QDomElement getProdElement();

    Serializable *mStart;
    Serializable *mDestination;
    Serializable *mVia;
    Serializable *mDate;
    Serializable *mFlags;
    bool mHasVia;
};

#endif // SBBCONNECTIONQUERY_H
