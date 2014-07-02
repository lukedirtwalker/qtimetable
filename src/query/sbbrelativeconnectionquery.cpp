#include "sbbrelativeconnectionquery.h"

SBBRelativeConnectionQuery::SBBRelativeConnectionQuery(QString context, eTimeType type)
{
    this->initXMLFields();
    this->mContext = context;
    QString t;
    switch(type)
    {
        case B: t = "B"; break;
        case F: t = "F"; break;
    }
    domStaticElementAttributes_["scrDir"] = t;
}

SBBRelativeConnectionQuery::~SBBRelativeConnectionQuery()
{

}

void SBBRelativeConnectionQuery::initXMLFields()
{
    domStaticElementName_ = "ConScrReq";
    domStaticElementAttributes_.insert("scrDir","");
    domStaticElementAttributes_.insert("nrCons","4");
}

QDomDocument SBBRelativeConnectionQuery::toXML()
{
    this->clear();
    QDomElement reqC = queryContainer_.toXML(*this);
    QDomElement conScrReq = Serializable::toXML(*this);
    QDomElement conResCtxt = this->createElement("ConResCtxt");
    QDomText t = this->createTextNode(this->mContext);
    conResCtxt.appendChild(t);
    conScrReq.appendChild(conResCtxt);
    reqC.appendChild(conScrReq);
    this->appendChild(reqC);
    return *this;
}
