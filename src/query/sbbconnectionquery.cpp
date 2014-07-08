#include "sbbconnectionquery.h"

SBBConnectionQuery::SBBConnectionQuery(Serializable *start, Serializable *dest,
                                       Serializable *date, Serializable *flags,
                                       Serializable *via)
    : SBBQuery("ConReq"), start_(start), destination_(dest), via_(via),
      date_(date), flags_(flags) {}

SBBConnectionQuery::~SBBConnectionQuery()
{
    delete start_;
    delete destination_;
    if(via_)
        delete via_;
    delete date_;
    delete flags_;
}

QDomElement SBBConnectionQuery::getProdElement()
{
    QDomElement prod = createElement("Prod");
    prod.setAttribute("prod","1111111111000000");
    return prod;
}

QDomDocument SBBConnectionQuery::toXML()
{
    clear();
    QDomElement reqC = queryContainer_.toXML(*this);
    QDomElement conReq = createElement(domStaticElementName_);

    QDomElement start = createElement("Start");
    start.appendChild(start_->toXML(*this));
    start.appendChild(getProdElement());
    conReq.appendChild(start);

    QDomElement destination = createElement("Dest");
    destination.appendChild(destination_->toXML(*this));
    conReq.appendChild(destination);

    if(via_)
    {
        QDomElement via = createElement("Via");
        via.appendChild(via_->toXML(*this));
        via.appendChild(getProdElement());
        conReq.appendChild(via);
    }

    conReq.appendChild(date_->toXML(*this));
    conReq.appendChild(flags_->toXML(*this));
    reqC.appendChild(conReq);
    appendChild(reqC);
    return *this;
}
