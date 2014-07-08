#ifndef SBBCONNECTIONQUERY_H
#define SBBCONNECTIONQUERY_H

#include "sbbquery.h"
#include "../util/serializable.h"

class SBBConnectionQuery : public SBBQuery
{
public:
    SBBConnectionQuery() : SBBQuery("ConReq"),
        start_{}, destination_{}, via_{}, date_{}, flags_{} {}
    SBBConnectionQuery(Serializable *start, Serializable *dest,
                       Serializable *date, Serializable *flags,
                       Serializable *via = nullptr);
    virtual ~SBBConnectionQuery(); //TODO why virtual

    virtual QDomDocument toXML();

private:
    QDomElement getProdElement();

    Serializable *start_;
    Serializable *destination_;
    Serializable *via_;
    Serializable *date_;
    Serializable *flags_;
};

#endif // SBBCONNECTIONQUERY_H
