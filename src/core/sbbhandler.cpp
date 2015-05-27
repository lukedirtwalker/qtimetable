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

#include "sbbhandler.h"

#include <QDomNode>
#include <QDomDocument>
#include <QNetworkReply>

#include "../net/sbbrequest.h"

SBBHandler::SBBHandler(QObject *parent) : QObject(parent),
    pendingRequest_{nullptr}, state_{H_STOPPED} {}

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
