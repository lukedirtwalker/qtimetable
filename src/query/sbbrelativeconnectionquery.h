#ifndef SBBRELATIVECONNECTIONQUERY_H
#define SBBRELATIVECONNECTIONQUERY_H

#include "../query/sbbquery.h"
#include "../util/globalshared.h"

class SBBRelativeConnectionQuery : public SBBQuery
{
public:
    SBBRelativeConnectionQuery(QString context, eTimeType type);
    virtual ~SBBRelativeConnectionQuery();

    virtual QDomDocument toXML();

private:
    void initXMLFields();

    QString mContext;
};

#endif // SBBRELATIVECONNECTIONQUERY_H
