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

#include "connectionstepitem.h"

#include <QDebug>

ConnectionStepItem::ConnectionStepItem(QDomNode domConnectionStep, QDateTime date, QObject *parent)
    : ListItem(parent)
{
    QDomElement el = domConnectionStep.toElement();

//    QString elString;
//    QTextStream stream(&elString);
//    el.save(stream, 4);
//    qDebug() << elString;

    QDomNode domDeparture = el.elementsByTagName(QStringLiteral("Departure")).at(0).toElement().elementsByTagName(QStringLiteral("BasicStop")).at(0);
    QDomNodeList domJourney = el.elementsByTagName(QStringLiteral("Journey"));
    QDomNodeList domWalk = el.elementsByTagName(QStringLiteral("Walk"));
    QDomNodeList domFoot = el.elementsByTagName(QStringLiteral("GisRoute"));
    QDomNode domArrival = el.elementsByTagName(QStringLiteral("Arrival")).at(0).toElement().elementsByTagName(QStringLiteral("BasicStop")).at(0);

    departure_ = new StopItem(domDeparture,date, this);
    arrival_ = new StopItem(domArrival,date, this);

    if(domJourney.count())
        journey_ = new Journey(domJourney.at(0), date);
    else if(domWalk.count())
        journey_ = new Journey(domWalk.at(0), date, true);
    else if(domFoot.count())
        journey_ = new Journey("Walk");
    else
        journey_ = new Journey("");

    if((domJourney.count() + domWalk.count() + domFoot.count()) > 1)
        qDebug() << "ConnectionStep has several journey types";
}

ConnectionStepItem::~ConnectionStepItem()
{
    if(journey_)
        delete journey_;
}

QVariant ConnectionStepItem::data(int role) const
{
    switch(role)
    {
    case DepStationRole: return departure_->getName();
    case DepTimeRole: return departure_->getTime();
    case DepPlatformRole: return departure_->getPlatform();
    case ArrSationRole: return arrival_->getName();
    case ArrTimeRole: return arrival_->getTime();
    case ArrPlatformRole: return arrival_->getPlatform();
    case MeansOfTransportRole: return journey_->getMeansOfTransport();
    case MeansOfTransportDetailRole: return journey_->getMeansOfTransportDetail();
    case DirectionRole: return journey_->getDirection();
    case UtilisationFirstRole: return departure_->getUtilisationFirst();
    case UtilisationSecondRole: return departure_->getUtilisationSecond();
    case HasDepDelayRole: return departure_->hasDelay();
    case HasArrDealayRole: return arrival_->hasDelay();
    case DepDelayRole: return departure_->getDelay();
    case ArrDelayRole: return arrival_->getDelay();
    case HasMeansOfTransportationRole: return journey_->hasMeansOfTransportation();
    case DepartureLatitudeRole: return departure_->getLatitude();
    case DepartureLongitudeRole: return departure_->getLongitude();
    case ArrivalLatitudeRole: return arrival_->getLatitude();
    case ArrivalLongitudeRole: return arrival_->getLongitude();
    case ChangedDeparturePlatformRole: return departure_->hasChangedPlatform();
    case ChangedArrivalPlatformRole: return arrival_->hasChangedPlatform();
    default: return QVariant();
    }
}

QHash<int,QByteArray> ConnectionStepItem::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DepStationRole] = "DepStation";
    names[DepTimeRole] = "DepTime";
    names[DepPlatformRole] = "DepPlatform";
    names[ArrSationRole] = "ArrStation";
    names[ArrTimeRole] = "ArrTime";
    names[ArrPlatformRole] = "ArrPlatform";
    names[MeansOfTransportRole] = "MeansOfTransport";
    names[MeansOfTransportDetailRole] = "MOTDetail";
    names[DirectionRole] = "Direction";
    names[UtilisationFirstRole] = "UtilisationFirst";
    names[UtilisationSecondRole] = "UtilisationSecond";
    names[HasDepDelayRole] = "HasDepDelay";
    names[HasArrDealayRole] = "HasArrDelay";
    names[DepDelayRole] = "DepDelay";
    names[ArrDelayRole] = "ArrDelay";
    names[HasMeansOfTransportationRole] = "HasMeansOfTransportation";
    names[DepartureLatitudeRole] = "DepartureLatitude";
    names[DepartureLongitudeRole] = "DepartureLongitude";
    names[ArrivalLatitudeRole] = "ArrivalLatitude";
    names[ArrivalLongitudeRole] = "ArrivalLongitude";
    names[ChangedDeparturePlatformRole] = "HasChangedDepPlatform";
    names[ChangedArrivalPlatformRole] = "HasChangedArrPlatform";
    return names;
}

bool ConnectionStepItem::setData(const QVariant &value, int role)
{
    Q_UNUSED(value)
    Q_UNUSED(role)
    return false;
}

QList<StopItem *> ConnectionStepItem::getStopovers()
{
    return journey_->getStopovers();
}
