#ifndef SBBQUERY_H
#define SBBQUERY_H

#include <QDomDocument>

#include "sbbquerycontainer.h"

class SBBQuery : public QDomDocument, public Serializable
{
public:
    SBBQuery(QString domElemName = "") : QDomDocument(),
        Serializable(domElemName) {}
    virtual ~SBBQuery() {}

    virtual QDomDocument toXML();

protected:
    SBBQueryContainer queryContainer_;
};

#endif // SBBQUERY_H
