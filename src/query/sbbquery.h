#ifndef SBBQUERY_H
#define SBBQUERY_H

#include <QDomDocument>

#include "sbbquerycontainer.h"

class SBBQuery : public QDomDocument, public Serializable
{
public:
    SBBQuery() : QDomDocument() {}
    virtual ~SBBQuery() {}

    virtual QDomDocument toXML();

protected:
    SBBQueryContainer queryContainer_;
};

#endif // SBBQUERY_H
