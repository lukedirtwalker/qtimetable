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

#ifndef SBBCONNECTIONHANDLER_H
#define SBBCONNECTIONHANDLER_H

#include "../listitems/connectionitem.h"
#include "sbbhandler.h"

class LocationItem;

class SBBConnectionHandler : public SBBHandler
{
    Q_OBJECT
public:
    SBBConnectionHandler(QObject *parent = nullptr) : SBBHandler(parent) {}

    void startConnectionSearch(QSharedPointer<LocationItem> depStation,
                               QSharedPointer<LocationItem> arrStation,
                               QDateTime d, bool isArrival);

    void startConnectionSearch(QSharedPointer<LocationItem> depStation,
                               QSharedPointer<LocationItem> arrStation,
                               QSharedPointer<LocationItem> viaStation,
                               QDateTime d, bool isArrival);

    void searchEarlier();
    void searchLater();
    void stopConnectionSearch();

    inline QList<QSharedPointer<ConnectionItem> > getAvailableConnections();

public slots:
    virtual void parseXMLResponse(QDomDocument xml);
    virtual void parseHTMLResponse(QString html);
    virtual void parseNoTypeResponse(QByteArray data);

private:
    QString searchContext_;
    QList<QSharedPointer<ConnectionItem> > SBBConnections_;
};

inline QList<QSharedPointer<ConnectionItem> > SBBConnectionHandler::getAvailableConnections()
{ return SBBConnections_;}

#endif // SBBCONNECTIONHANDLER_H
