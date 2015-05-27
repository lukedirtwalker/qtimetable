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

#ifndef CONNECTIONSTEPITEMNEW_H
#define CONNECTIONSTEPITEMNEW_H

#include "stopitem.h"
#include "../domin/journey.h"

class ConnectionStepItem : public ListItem
{
    Q_OBJECT
public:
    ConnectionStepItem(QObject *parent = nullptr) : ListItem(parent),
    departure_{nullptr}, arrival_{nullptr}, journey_{nullptr} {}
    ConnectionStepItem(QDomNode domConnectionStep, QDateTime date, QObject *parent = nullptr);
    ~ConnectionStepItem();

    QList<StopItem *> getStopovers();

    QVariant data(int role) const;
    QHash<int,QByteArray> roleNames() const;
    bool setData(const QVariant &value, int role);

    inline QDateTime getDepTime() const;
    inline QDateTime getArrTime() const;
    inline QString getDepName() const;
    inline QString getArrName() const;
    inline QString getDepPlatform() const;
    inline QString getArrPlatform() const;
    inline QString getMeansOfTransport() const;
    inline QString getDepDelay() const;
    inline QString getArrDelay() const;
    inline bool hasDepDelay() const;
    inline bool hasArrDelay() const;
    inline bool hasChangedDeparturePlatform() const;
    inline bool hasChangedArrivalPlatform() const;
    inline bool hasMeansOfTransportation() const;
    inline int getUtilisationFirst() const;
    inline int getUtilisationSecond() const;
    inline double getDepartureLatitude() const;
    inline double getDepartureLongitude() const;
    inline double getArrivalLatitude() const;
    inline double getArrivalLongitude() const;

    enum Roles{
        DepStationRole=Qt::UserRole+1,
        DepTimeRole,
        DepPlatformRole,
        ArrSationRole,
        ArrTimeRole,
        ArrPlatformRole,
        MeansOfTransportRole,
        MeansOfTransportDetailRole,
        DirectionRole,
        UtilisationFirstRole,
        UtilisationSecondRole,
        HasDepDelayRole,
        HasArrDealayRole,
        DepDelayRole,
        ArrDelayRole,
        HasMeansOfTransportationRole,
        DepartureLatitudeRole,
        DepartureLongitudeRole,
        ArrivalLatitudeRole,
        ArrivalLongitudeRole,
        ChangedDeparturePlatformRole,
        ChangedArrivalPlatformRole
    };

private:
    StopItem *departure_;
    StopItem *arrival_;
    Journey *journey_;
};

inline QDateTime ConnectionStepItem::getDepTime() const { return departure_->getTime();}

inline QDateTime ConnectionStepItem::getArrTime() const { return arrival_->getTime();}

inline QString ConnectionStepItem::getDepName() const { return departure_->getName();}

inline QString ConnectionStepItem::getArrName() const { return arrival_->getName();}

inline QString ConnectionStepItem::getDepPlatform() const { return departure_->getPlatform();}

inline QString ConnectionStepItem::getArrPlatform() const { return arrival_->getPlatform();}

inline QString ConnectionStepItem::getMeansOfTransport() const { return journey_->getMeansOfTransport();}

inline QString ConnectionStepItem::getDepDelay() const { return departure_->getDelay();}

inline QString ConnectionStepItem::getArrDelay() const { return arrival_->getDelay();}

inline bool ConnectionStepItem::hasDepDelay() const { return departure_->hasDelay();}

inline bool ConnectionStepItem::hasArrDelay() const { return arrival_->hasDelay();}

inline bool ConnectionStepItem::hasChangedDeparturePlatform() const { return departure_->hasChangedPlatform();}

inline bool ConnectionStepItem::hasMeansOfTransportation() const { return journey_->hasMeansOfTransportation();}

inline int ConnectionStepItem::getUtilisationFirst() const { return departure_->getUtilisationFirst();}

inline int ConnectionStepItem::getUtilisationSecond() const { return departure_->getUtilisationSecond();}

inline double ConnectionStepItem::getDepartureLatitude() const { return departure_->getLatitude();}

inline double ConnectionStepItem::getDepartureLongitude() const { return departure_->getLongitude();}

inline double ConnectionStepItem::getArrivalLatitude() const { return arrival_->getLatitude();}

inline double ConnectionStepItem::getArrivalLongitude() const { return arrival_->getLongitude();}

inline bool ConnectionStepItem::hasChangedArrivalPlatform() const { return arrival_->hasChangedPlatform();}

#endif // CONNECTIONSTEPITEMNEW_H
