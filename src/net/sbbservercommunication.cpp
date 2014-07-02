#include "sbbservercommunication.h"
#include "../core/sbbhandler.h"

SBBServerCommunication::SBBServerCommunication()
    : serverUrl_{QUrl("http://xmlfahrplan.sbb.ch/bin/extxml.exe/")}
{}

void SBBServerCommunication::sendRequest(SBBRequest *request)
{
    QNetworkRequest netRequest(serverUrl_);
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader,request->getContentType());
    QNetworkReply *r = networkAccessManager_.post(netRequest,request->getSBBQuery()->toXML().toString().toLatin1());
    request->setReply(r);
    SBBHandler *h = request->getHandler();
    connect(r,SIGNAL(finished()),h,SLOT(parseResponse()));

    //Debugger::getInstance()->visualizeXML(request->getSBBQuery()->toXML().documentElement().toElement());
}

void SBBServerCommunication::abortRequest(SBBRequest *r)
{
    if(r->getReply() == NULL)
        return;
    if(r->getReply()->isRunning())
    {
        disconnect(r->getReply(),SIGNAL(finished()),r->getHandler(),SLOT(parseResponse()));
        r->getReply()->abort();
    }
    r->getReply()->deleteLater();
}
