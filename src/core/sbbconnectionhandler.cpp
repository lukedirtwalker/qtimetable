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

//#include "util/debugger.h"

SBBConnectionHandler::SBBConnectionHandler() : SBBHandler()
{

}

void SBBConnectionHandler::startConnectionSearch(LocationItem *depStation, LocationItem *arrStation, QDateTime d, bool isArrival)
{
    qDebug() << depStation->getExternalId() << arrStation->getExternalId();
    mSearchContext = "";

    if(state_ != H_STOPPED)
        stopConnectionSearch();

    Serializable *start,*dest;

    if(depStation->getExternalId().isEmpty())
        start = new DomAddress(depStation->stationName(), depStation->getLatitude(), depStation->getLongitude());
    else
        start = new DomStation(depStation->stationName(), depStation->getExternalId());

    if(arrStation->getExternalId().isEmpty())
        dest = new DomAddress(arrStation->stationName(), arrStation->getLatitude(), arrStation->getLongitude());
    else
        dest = new DomStation(arrStation->stationName(), arrStation->getExternalId());

    DomDate *date = new DomDate(d,isArrival);

    DomFlags *flags = isArrival ? new DomFlags(B) : new DomFlags(F);

    SBBConnectionQuery *q = new SBBConnectionQuery(start,dest,date,flags);
    sendRequest(new SBBRequest(q,"application/xml", this));
    setState(H_STARTED);
}


void SBBConnectionHandler::startConnectionSearch(QString startName, QString startExternalId, QString startLatitude, QString startLongitude, QString destName, QString destExternalId, QString destLatitude, QString destLongitude, QDateTime d, bool isArrival)
{
    this->mSearchContext = "";

    if(this->getState() != H_STOPPED)
    {
        this->stopConnectionSearch();
    }

    Serializable *start,*dest;

    if(startExternalId.isEmpty())
        start = new DomAddress(startName, startLatitude, startLongitude);
    else
        start = new DomStation(startName,startExternalId);

    if(destExternalId.isEmpty())
        dest = new DomAddress(destName, destLatitude, destLongitude);
    else
        dest = new DomStation(destName,destExternalId);

    DomDate *date = new DomDate(d,isArrival);

    DomFlags *flags;
    if(isArrival)
    {
        flags = new DomFlags(B);
    }
    else
    {
        flags = new DomFlags(F);
    }

    SBBConnectionQuery *q = new SBBConnectionQuery(start,dest,date,flags);
    this->sendRequest(new SBBRequest(q,"application/xml", this));
    this->setState(H_STARTED);
}

void SBBConnectionHandler::startConnectionSearch(QString startName, QString startExternalId, QString startLatitude, QString startLongitude, QString destName, QString destExternalId, QString destLatitude, QString destLongitude, QString viaName, QString viaExternalId, QString viaLatitude, QString viaLongitude, QDateTime d, bool isArrival)
{
    this->mSearchContext = "";

    if(this->getState() != H_STOPPED)
    {
        this->stopConnectionSearch();
    }

    Serializable *start,*dest,*via;

    if(startExternalId.isEmpty())
        start = new DomAddress(startName, startLatitude, startLongitude);
    else
        start = new DomStation(startName,startExternalId);

    if(destExternalId.isEmpty())
        dest = new DomAddress(destName, destLatitude, destLongitude);
    else
        dest = new DomStation(destName,destExternalId);

    if(viaExternalId.isEmpty())
        via = new DomAddress(viaName, viaLatitude, viaLongitude);
    else
        via = new DomStation(viaName,viaExternalId);

    DomDate *date = new DomDate(d,isArrival);

    DomFlags *flags;
    if(isArrival)
    {
        flags = new DomFlags(B);
    }
    else
    {
        flags = new DomFlags(F);
    }

    SBBConnectionQuery *q = new SBBConnectionQuery(start,dest,via,date,flags);
    this->sendRequest(new SBBRequest(q,"application/xml", this));
    this->setState(H_STARTED);
}

void SBBConnectionHandler::searchEarlier()
{
    if(this->getState() == H_READY)
    {
        SBBRelativeConnectionQuery *q = new SBBRelativeConnectionQuery(this->mSearchContext,B);
        this->sendRequest(new SBBRequest(q,"application/xml", this));
        this->setState(H_EARLIER);
    }
}

void SBBConnectionHandler::searchLater()
{
    if(this->getState() == H_READY)
    {
        SBBRelativeConnectionQuery *q = new SBBRelativeConnectionQuery(this->mSearchContext,F);
        this->sendRequest(new SBBRequest(q,"application/xml", this));
        this->setState(H_LATER);
    }
}

void SBBConnectionHandler::stopConnectionSearch()
{
    if(this->getState() != H_STOPPED)
    {
        this->stopRequest();
        qDeleteAll(this->mSBBConnections);
        this->mSBBConnections.clear();
        this->setState(H_STOPPED);
    }
}

void SBBConnectionHandler::parseXMLResponse(QDomDocument xml)
{
    if (!xml.documentElement().elementsByTagName("Err").at(0).isNull())
    {
        QString errCode = xml.documentElement().elementsByTagName("Err").at(0).toElement().attributeNode("code").value();
        if(errCode == "K890")
        {
            emit parsingFinished(NO_CONNECTIONS_RESPONSE);
        }
        else
        {
            SBBErrorMessage_ = QString(errCode + " ");
            SBBErrorMessage_ += xml.documentElement().elementsByTagName("Err").at(0).toElement().attributeNode("text").value();
            emit parsingFinished(XML_ERROR_RESPONSE);
        }
        return;
    }

    this->mSearchContext = xml.documentElement().elementsByTagName("ConResCtxt").at(0).toElement().text().toLatin1();

    QDomNodeList domConnections = xml.documentElement().elementsByTagName("Connection");
    int nConnections = domConnections.count();
    if(!nConnections)
    {
        emit parsingFinished(XML_PARSING_ERROR);
        return;
    }

    QList<ConnectionItem*> newSBBConnections;
    for(int i=0;i<nConnections;i++)
    {
        QDomNode domConnection = domConnections.at(i);
        ConnectionItem *c = new ConnectionItem(domConnection);
        newSBBConnections.append(c);
    }

    switch(this->getState())
    {
        case H_STARTED:
        {
            this->mSBBConnections = newSBBConnections;
            break;
        }
        case H_EARLIER:
        {
            QListIterator<ConnectionItem*> it(newSBBConnections);
            QList<ConnectionItem*> tmp = this->mSBBConnections;
            this->mSBBConnections.clear();
            while(it.hasNext())
            {
                this->mSBBConnections.append(it.next());
            }
            it = QListIterator<ConnectionItem*>(tmp);
            while(it.hasNext())
            {
                this->mSBBConnections.append(it.next());
            }
            break;
        }
        case H_LATER:
        {
            QListIterator<ConnectionItem*> it(newSBBConnections);
            while(it.hasNext())
            {
                this->mSBBConnections.append(it.next());
            }
            break;
        }
    }
    newSBBConnections.clear();
    qDebug() << "parsing done!";
    emit this->parsingFinished(AOK);
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

void SBBConnectionHandler::parseNoTypeResponse(QByteArray data)
{
    emit this->parsingFinished(NOTYPE_ERROR);
}

QList<ConnectionItem*> SBBConnectionHandler::getAvailableConnections()
{
    return this->mSBBConnections;
}
