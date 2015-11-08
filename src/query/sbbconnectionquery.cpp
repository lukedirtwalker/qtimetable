/******************************************************************************
*Copyright (c) 2013-2015, Lukas Vogel, Stefan Willi
*All rights reserved.
*
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions are met:
*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*    * Neither the name of the <organization> nor the
*      names of its contributors may be used to endorse or promote products
*      derived from this software without specific prior written permission.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
*DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

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
    delete via_;
    delete date_;
    delete flags_;
}

QDomElement SBBConnectionQuery::getProdElement(QDomDocument& doc)
{
    QDomElement prod = doc.createElement("Prod");
    prod.setAttribute("prod","1111111111000000");
    return prod;
}

QDomDocument SBBConnectionQuery::toXML()
{
    QDomDocument doc;
    QDomElement reqC = queryContainer_.toXML(doc);
    QDomElement conReq = doc.createElement(domStaticElementName_);

    QDomElement start = doc.createElement("Start");
    start.appendChild(start_->toXML(doc));
    start.appendChild(getProdElement(doc));
    conReq.appendChild(start);

    QDomElement destination = doc.createElement("Dest");
    destination.appendChild(destination_->toXML(doc));
    conReq.appendChild(destination);

    if(via_)
    {
        QDomElement via = doc.createElement("Via");
        via.appendChild(via_->toXML(doc));
        via.appendChild(getProdElement(doc));
        conReq.appendChild(via);
    }

    conReq.appendChild(date_->toXML(doc));
    conReq.appendChild(flags_->toXML(doc));
    reqC.appendChild(conReq);
    doc.appendChild(reqC);
    return doc;
}
