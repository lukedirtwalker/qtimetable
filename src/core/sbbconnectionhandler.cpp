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
        QSharedPointer<LocationItem> depStation,
        QSharedPointer<LocationItem> arrStation,
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

void SBBConnectionHandler::startConnectionSearch(
        QSharedPointer<LocationItem> depStation,
        QSharedPointer<LocationItem> arrStation,
        QSharedPointer<LocationItem> viaStation,
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
    if(!xml.documentElement().elementsByTagName("Err").at(0).isNull())
    {
        QString errCode = xml.documentElement().elementsByTagName("Err")
                .at(0).toElement().attributeNode("code").value();
        if(errCode == "K890")
            emit parsingFinished(NO_CONNECTIONS_RESPONSE);
        else
        {
            SBBErrorMessage_ = QString(errCode + " ");
            SBBErrorMessage_ += xml.documentElement().elementsByTagName("Err")
                    .at(0).toElement().attributeNode("text").value();
            emit parsingFinished(XML_ERROR_RESPONSE);
        }
        return;
    }

    searchContext_ = xml.documentElement().elementsByTagName("ConResCtxt")
            .at(0).toElement().text().toLatin1();

    QDomNodeList domConnections = xml.documentElement()
            .elementsByTagName("Connection");
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
    QString titleStartTag = "<title>";
    QString titleEndTag = "</title>";

    if(html.contains(titleStartTag))
    {
        int start = html.indexOf(titleStartTag)+titleStartTag.length();
        int end = html.indexOf(titleEndTag);
        SBBErrorMessage_ = html.mid(start,end-start);
    }
    emit this->parsingFinished(HTML_ERROR_RESPONSE);
}

void SBBConnectionHandler::parseNoTypeResponse(QByteArray)
{
    emit parsingFinished(NOTYPE_ERROR);
}
