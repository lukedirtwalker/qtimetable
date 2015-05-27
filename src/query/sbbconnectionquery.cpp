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
