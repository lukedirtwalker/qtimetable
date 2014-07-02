#include "sbbconnectionquery.h"

SBBConnectionQuery::SBBConnectionQuery()
{
    this->initXMLFields();
    this->mHasVia = false;
    this->mStart = NULL;
    this->mDestination = NULL;
    this->mVia = NULL;
    this->mDate = NULL;
    this->mFlags = NULL;
}

SBBConnectionQuery::~SBBConnectionQuery()
{
    delete this->mStart;
    delete this->mDestination;
    if(this->mVia)
        delete this->mVia;
    delete this->mDate;
    delete this->mFlags;
}

SBBConnectionQuery::SBBConnectionQuery(Serializable *start, Serializable *dest, Serializable *via, Serializable *date, Serializable *flags)
{
    this->initXMLFields();
    this->mStart = start;
    this->mDestination = dest;
    this->mVia = via;
    this->mHasVia = true;
    this->mDate = date;
    this->mFlags = flags;
}

SBBConnectionQuery::SBBConnectionQuery(Serializable *start, Serializable *dest, Serializable *date, Serializable *flags)
{
    this->initXMLFields();
    this->mStart = start;
    this->mDestination = dest;
    this->mVia = NULL;
    this->mHasVia = false;
    this->mDate = date;
    this->mFlags = flags;
}

QDomElement SBBConnectionQuery::getProdElement()
{
    QDomElement prod = this->createElement("Prod");
    prod.setAttribute("prod","1111111111000000");
    return prod;
}

QDomDocument SBBConnectionQuery::toXML()
{
    this->clear();
    QDomElement reqC = queryContainer_.toXML(*this);
    QDomElement conReq = this->createElement(domStaticElementName_);

    QDomElement start = this->createElement("Start");
    start.appendChild(this->mStart->toXML(*this));
    start.appendChild(this->getProdElement());
    conReq.appendChild(start);

    QDomElement destination = this->createElement("Dest");
    destination.appendChild(this->mDestination->toXML(*this));
    conReq.appendChild(destination);

    if(this->mHasVia)
    {
        QDomElement via = this->createElement("Via");
        via.appendChild(this->mVia->toXML(*this));
        via.appendChild(this->getProdElement());
        conReq.appendChild(via);
    }

    conReq.appendChild(this->mDate->toXML(*this));
    conReq.appendChild(this->mFlags->toXML(*this));
    reqC.appendChild(conReq);
    this->appendChild(reqC);
    return *this;
}

void SBBConnectionQuery::initXMLFields()
{
    domStaticElementName_ = "ConReq";
}
