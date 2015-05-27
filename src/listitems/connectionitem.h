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

#ifndef CONNECTIONITEMNEW_H
#define CONNECTIONITEMNEW_H

#include "listitem.h"
#include "../util/duration.h"
#include "../util/globalshared.h"
#include "../listmodels/connectionstepmodel.h"

#include "connectionstepitem.h"

class QDomNode;

class ConnectionItem : public ListItem
{
    Q_OBJECT
public:
    ConnectionItem(QObject *parent = nullptr) : ListItem(parent) {}
    ConnectionItem(QDomNode domConnection, QObject *parent = nullptr);

    virtual QVariant data(int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    bool setData(const QVariant &value, int role);

    inline ConnectionStepModel *getConnectionSteps() const;
    inline void setConnectionStateInfo(int info);
    inline bool hasConnectionStateInformation() const;

    enum Roles{
        DepRole=Qt::UserRole+1,
        ArrRole,
        DurRole,
        ChgRole,
        PlatRole,
        UtilisationFirstRole,
        UtilisationSecRole,
        ConnectionStateInfoRole,
        HasChangedDeparturePlatformRole
    };

private:
    void createOverview();

    bool hasChangedDeparturePlatform_;
    bool hasIrregularServiceDays_;
    bool hasCSInformation_;
    QString platform_;
    QString serviceDays_;
    QString id_;
    QDateTime date_;
    QDateTime departureTime_;
    QDateTime arrivalTime_;
    Duration duration_;
    int nrChanges_;
    int utilisationFirst_;
    int utilisationSecond_;

    QVector<QString> connectionVehicles_;
    QVector<eConnectionStateInformation> connectionStateInformations_;
    ConnectionStepModel *connectionSteps_;

    int connectionStateInfo_;
};

inline ConnectionStepModel *ConnectionItem::getConnectionSteps() const
{ return connectionSteps_;}

inline bool ConnectionItem::hasConnectionStateInformation() const
{ return hasCSInformation_;}

inline void ConnectionItem::setConnectionStateInfo(int info)
{ connectionStateInfo_ = info;}

#endif // CONNECTIONITEMNEW_H
