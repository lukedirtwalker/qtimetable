#include "sbbservercommunication.h"

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include "../core/sbbhandler.h"
#include "../net/sbbrequest.h"

SBBServerCommunication::SBBServerCommunication()
    : serverUrl_{QUrl("http://xmlfahrplan.sbb.ch/bin/extxml.exe/")}
{}

void SBBServerCommunication::sendRequest(SBBRequest *request)
{
    QNetworkRequest netRequest(serverUrl_);
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader,
                         request->getContentType());
    QNetworkReply *r = networkAccessManager_
            .post(netRequest, request->getSBBQuery()->toXML().toString().toLatin1());
    request->setReply(r);

    connect(r, &QNetworkReply::finished,
            request->getHandler(), &SBBHandler::parseResponse);
}

void SBBServerCommunication::abortRequest(SBBRequest *r)
{
    auto reply = r->getReply();
    if(!reply)
        return;
    if(reply->isRunning())
    {
        disconnect(reply, &QNetworkReply::finished,
                   r->getHandler(), &SBBHandler::parseResponse);
        reply->abort();
    }
    reply->deleteLater();
}
