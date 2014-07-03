#include "sbbhandler.h"

SBBHandler::SBBHandler() : pendingRequest_{nullptr}, state_{H_STOPPED}
{}

void SBBHandler::setState(eSBBHandlerState s)
{
    state_ = s;
}

eSBBHandlerState SBBHandler::getState()
{
    return state_;
}

QString SBBHandler::getErrorMessage()
{
    return SBBErrorMessage_;
}

void SBBHandler::parseResponse()
{
    bool parsed = false;
    QNetworkReply *r = qobject_cast<QNetworkReply *>(sender());
    QByteArray data = r->readAll();
    r->deleteLater();

    QDomDocument xml;
    xml.setContent(data);
    QDomElement docElement = xml.documentElement();
    if(!xml.isNull() && !docElement.isNull())
    {
        this->parseXMLResponse(xml);
        parsed = true;
    }

    QString html(data);
    if(!parsed && html.contains("<!DOCTYPE HTML PUBLIC "))
    {
        this->parseHTMLResponse(html);
        parsed = true;
    }

    if(!parsed)
    {
        this->parseNoTypeResponse(data);
        parsed = true;
    }
    this->setState(H_READY);
}

void SBBHandler::sendRequest(SBBRequest *r)
{
    if(this->pendingRequest_)
    {
        delete this->pendingRequest_;
        this->pendingRequest_ = r;
    }
    else
    {
        this->pendingRequest_ = r;
    }
    this->SBBServerCommunication_.sendRequest(this->pendingRequest_);
}

void SBBHandler::stopRequest()
{
    if(this->pendingRequest_)
    {
        if(this->getState() != H_READY)
        {
            this->SBBServerCommunication_.abortRequest(this->pendingRequest_);
        }
        delete this->pendingRequest_;
        this->pendingRequest_ = NULL;
    }
}
