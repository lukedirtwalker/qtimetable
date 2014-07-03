#include "sbbhandler.h"

SBBHandler::SBBHandler() : pendingRequest_{nullptr}, state_{H_STOPPED}
{}

void SBBHandler::parseResponse()
{
    QNetworkReply *r = qobject_cast<QNetworkReply *>(sender());
    QByteArray data = r->readAll();
    r->deleteLater();

    QDomDocument xml;
    xml.setContent(data);
    QDomElement docElement = xml.documentElement();
    if(!xml.isNull() && !docElement.isNull())
        parseXMLResponse(xml);
    else if(QString(data).contains("<!DOCTYPE HTML PUBLIC "))
        parseHTMLResponse(QString(data));
    else
        parseNoTypeResponse(data);
    state_ = H_READY;
}

void SBBHandler::sendRequest(SBBRequest *r)
{
    if(pendingRequest_)
        delete pendingRequest_;
    pendingRequest_ = r;
    SBBServerCommunication_.sendRequest(pendingRequest_);
}

void SBBHandler::stopRequest()
{
    if(pendingRequest_)
    {
        if(state_ != H_READY)
            SBBServerCommunication_.abortRequest(pendingRequest_);
        delete pendingRequest_;
        pendingRequest_ = nullptr;
    }
}
