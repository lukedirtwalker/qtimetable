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

#include "sbbconnectionhandler.h"

#include <QDebug>

#include "../query/sbbconnectionquery.h"
#include "../query/sbbrelativeconnectionquery.h"
#include "../domout/domaddress.h"
#include "../domout/domstation.h"
#include "../domout/domflags.h"
#include "../domout/domdate.h"
#include "../net/sbbrequest.h"

#include "../listitems/locationitem.h"

#include "../util/qdomnodeiterator.h"

void SBBConnectionHandler::startConnectionSearch(
        const LocationItem* depStation,
        const LocationItem* arrStation,
        QDateTime d, bool isArrival)
{
    searchContext_ = "";

    if(state_ != H_STOPPED)
        stopConnectionSearch();

    Serializable *start,*dest;

    if(depStation->getExternalId().isEmpty())
        start = new DomAddress(depStation->stationName(),
                               depStation->getLatitude(),
                               depStation->getLongitude());
    else
        start = new DomStation(depStation->stationName(),
                               depStation->getExternalId());

    if(arrStation->getExternalId().isEmpty())
        dest = new DomAddress(arrStation->stationName(),
                              arrStation->getLatitude(),
                              arrStation->getLongitude());
    else
        dest = new DomStation(arrStation->stationName(),
                              arrStation->getExternalId());

    DomDate *date = new DomDate(d,isArrival);

    DomFlags *flags = isArrival ? new DomFlags(B) : new DomFlags(F);

    SBBConnectionQuery *q = new SBBConnectionQuery(start,dest,date,flags);
    sendRequest(new SBBRequest(q,"application/xml", this));
    state_ = H_STARTED;
}

void SBBConnectionHandler::startConnectionSearch(const LocationItem *depStation,
        const LocationItem *arrStation,
        const LocationItem *viaStation,
        QDateTime d, bool isArrival)
{
    searchContext_ = "";

    if(state_ != H_STOPPED)
        stopConnectionSearch();

    Serializable *start, *dest, *via;

    if(depStation->getExternalId().isEmpty())
        start = new DomAddress(depStation->stationName(),
                               depStation->getLatitude(),
                               depStation->getLongitude());
    else
        start = new DomStation(depStation->stationName(),
                               depStation->getExternalId());

    if(arrStation->getExternalId().isEmpty())
        dest = new DomAddress(arrStation->stationName(),
                              arrStation->getLatitude(),
                              arrStation->getLongitude());
    else
        dest = new DomStation(arrStation->stationName(),
                              arrStation->getExternalId());

    if(viaStation->getExternalId().isEmpty())
        via = new DomAddress(viaStation->stationName(),
                             viaStation->getLatitude(),
                             viaStation->getLongitude());
    else
        via = new DomStation(viaStation->stationName(),
                             viaStation->getExternalId());

    DomDate *date = new DomDate(d,isArrival);

    DomFlags *flags = isArrival ? new DomFlags(B) : new DomFlags(F);

    SBBConnectionQuery *q =
            new SBBConnectionQuery(start, dest, date, flags, via);
    sendRequest(new SBBRequest(q,"application/xml", this));
    state_ = H_STARTED;
}

void SBBConnectionHandler::searchEarlier()
{
    if(state_ == H_READY)
    {
        SBBRelativeConnectionQuery *q =
                new SBBRelativeConnectionQuery(searchContext_,B);
        this->sendRequest(new SBBRequest(q,"application/xml", this));
        state_ = H_EARLIER;
    }
}

void SBBConnectionHandler::searchLater()
{
    if(state_ == H_READY)
    {
        SBBRelativeConnectionQuery *q =
                new SBBRelativeConnectionQuery(searchContext_,F);
        sendRequest(new SBBRequest(q,"application/xml", this));
        state_ = H_LATER;
    }
}

void SBBConnectionHandler::stopConnectionSearch()
{
    if(state_ != H_STOPPED)
    {
        stopRequest();
        SBBConnections_.clear();
        state_ = H_STOPPED;
    }
}

void SBBConnectionHandler::parseXMLResponse(QDomDocument xml)
{
    auto errElement = xml.documentElement().elementsByTagName(QStringLiteral("Err")).at(0);
    if(!errElement.isNull())
    {
        QString errCode = errElement.toElement().attributeNode(QStringLiteral("code")).value();
        if(errCode == "K890")
            emit parsingFinished(NO_CONNECTIONS_RESPONSE);
        else
        {
            SBBErrorMessage_ = QString(errCode + " ");
            SBBErrorMessage_ += errElement.toElement().attributeNode(QStringLiteral("text")).value();
            emit parsingFinished(XML_ERROR_RESPONSE);
        }
        return;
    }

    searchContext_ = xml.documentElement().elementsByTagName(QStringLiteral("ConResCtxt"))
            .at(0).toElement().text().toLatin1();

    QDomNodeList domConnections = xml.documentElement()
            .elementsByTagName(QStringLiteral("Connection"));
    if(!domConnections.count())
    {
        emit parsingFinished(XML_PARSING_ERROR);
        return;
    }

    QList<QSharedPointer<ConnectionItem> > newSBBConnections;
    for(auto con : domConnections)
        newSBBConnections.append(
                    QSharedPointer<ConnectionItem>(new ConnectionItem(con)));

    if(H_STARTED == state_)
        SBBConnections_ = newSBBConnections;
    else if(H_EARLIER == state_)
    {
        newSBBConnections.append(SBBConnections_);
        SBBConnections_ = newSBBConnections;
    }
    else if(H_LATER == state_)
        SBBConnections_.append(newSBBConnections);

    newSBBConnections.clear();
    emit parsingFinished(AOK);
}

void SBBConnectionHandler::parseHTMLResponse(QString html)
{
    static const QLatin1String titleStartTag = QLatin1String("<title>");
    static const QLatin1String titleEndTag = QLatin1String("</title>");

    if(html.contains(titleStartTag))
    {
        int start = html.indexOf(titleStartTag)+titleStartTag.size();
        int end = html.indexOf(titleEndTag);
        SBBErrorMessage_ = html.mid(start,end-start);
    }
    emit this->parsingFinished(HTML_ERROR_RESPONSE);
}

void SBBConnectionHandler::parseNoTypeResponse(QByteArray)
{
    emit parsingFinished(NOTYPE_ERROR);
}
