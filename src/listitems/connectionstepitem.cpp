#include "connectionstepitem.h"

#include <QDebug>

ConnectionStepItem::ConnectionStepItem(QDomNode domConnectionStep, QDateTime date, QObject *parent)
    : ListItem(parent)
{
    QDomElement el = domConnectionStep.toElement();

    QDomNode domDeparture = el.elementsByTagName("Departure").at(0).toElement().elementsByTagName("BasicStop").at(0);
    QDomNodeList domJourney = el.elementsByTagName("Journey");
    QDomNodeList domWalk = el.elementsByTagName("Walk");
    QDomNodeList domFoot = el.elementsByTagName("GisRoute");
    QDomNode domArrival = el.elementsByTagName("Arrival").at(0).toElement().elementsByTagName("BasicStop").at(0);

    departure_ = new StopItem(domDeparture,date, this);
    arrival_ = new StopItem(domArrival,date, this);

    if(domJourney.count())
        journey_ = new Journey(domJourney.at(0), date);
    else if(domWalk.count() || domFoot.count())
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
