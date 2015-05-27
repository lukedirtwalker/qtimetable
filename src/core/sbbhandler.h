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

#ifndef SBBHANDLER_H
#define SBBHANDLER_H

#include "../net/sbbservercommunication.h"
#include "../util/globalshared.h"

class QDomDocument;

typedef enum {H_STOPPED,H_STARTED,H_EARLIER,H_LATER,H_READY} eSBBHandlerState;

class SBBHandler : public QObject
{
    Q_OBJECT
public:
    SBBHandler(QObject *parent = nullptr);

    inline QString getErrorMessage();

public slots:
    virtual void parseResponse();

signals:
    void parsingFinished(eStatusID id);

protected:
    virtual void parseXMLResponse(QDomDocument xml) = 0;
    virtual void parseHTMLResponse(QString html) = 0;
    virtual void parseNoTypeResponse(QByteArray data) = 0;


    virtual void sendRequest(SBBRequest *r);
    virtual void stopRequest();

    QString SBBErrorMessage_;
    SBBServerCommunication SBBServerCommunication_;
    SBBRequest *pendingRequest_;
    eSBBHandlerState state_;
};

inline QString SBBHandler::getErrorMessage() { return SBBErrorMessage_;}

#endif // SBBHANDLER_H
