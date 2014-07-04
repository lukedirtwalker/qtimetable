#include "connectionstepitem.h"

ConnectionStepItem::ConnectionStepItem(QDomNode domConnectionStep, QDateTime date, QObject *parent)
    : ListItem(parent)
{
    QDomElement el = domConnectionStep.toElement();

    QDomNode domDeparture = el.elementsByTagName("Departure").at(0).toElement().elementsByTagName("BasicStop").at(0);
    QDomNodeList domJourney = el.elementsByTagName("Journey");
    QDomNodeList domWalk = el.elementsByTagName("Walk");
    QDomNodeList domFoot = el.elementsByTagName("GisRoute");
    QDomNode domArrival = el.elementsByTagName("Arrival").at(0).toElement().elementsByTagName("BasicStop").at(0);

    this->mDeparture = new StopItem(domDeparture,date);
    this->mArrival = new StopItem(domArrival,date);

    if(domJourney.count())
    {
        this->mJourney = new Journey(domJourney.at(0),date);
    }
    else if(domWalk.count() || domFoot.count())
    {
        this->mJourney = new Journey("Walk");
    }
    else
    {
        this->mJourney = new Journey("");
    }

//    if((domJourney.count() + domWalk.count() + domFoot.count()) > 1)
//        TODO Debugger::getInstance()->print("ConnectionStep has several journey types");
}

ConnectionStepItem::~ConnectionStepItem()
{
    if(mDeparture)
        delete this->mDeparture;
    if(mArrival)
        delete this->mArrival;
    if(mJourney)
        delete this->mJourney;
}

QVariant ConnectionStepItem::data(int role) const
{
    switch(role)
    {
    case DepStationRole: return getDepName();
    case DepTimeRole: return getDepTime();
    case DepPlatformRole: return getDepPlatform();
    case ArrSationRole: return getArrName();
    case ArrTimeRole: return getArrTime();
    case ArrPlatformRole: return getArrPlatform();
    case MeansOfTransportRole: return getMeansOfTransport();
    case UtilisationFirstRole: return getUtilisationFirst();
    case UtilisationSecondRole: return getUtilisationSecond();
    case HasDepDelayRole: return hasDepDelay();
    case HasArrDealayRole: return hasArrDelay();
    case DepDelayRole: return getDepDelay();
    case ArrDelayRole: return getArrDelay();
    case HasMeansOfTransportationRole: return hasMeansOfTransportation();
    case DepartureLatitudeRole: return getDepartureLatitude();
    case DepartureLongitudeRole: return getDepartureLongitude();
    case ArrivalLatitudeRole: return getArrivalLatitude();
    case ArrivalLongitudeRole: return getArrivalLongitude();
    case ChangedDeparturePlatformRole: return hasChangedDeparturePlatform();
    case ChangedArrivalPlatformRole: return hasChangedArrivalPlatform();
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

QString ConnectionStepItem::getId() const
{
    return QString();
}

QList<StopItem *> ConnectionStepItem::getStopovers()
{
    return this->mJourney->getStopovers();
}

QDateTime ConnectionStepItem::getDepTime() const
{
    return this->mDeparture->getTime();
}

QDateTime ConnectionStepItem::getArrTime() const
{
    return this->mArrival->getTime();
}

QString ConnectionStepItem::getDepName() const
{
    return this->mDeparture->getName();
}

QString ConnectionStepItem::getArrName() const
{
    return this->mArrival->getName();
}

QString ConnectionStepItem::getDepPlatform() const
{
    return this->mDeparture->getPlatform();
}

QString ConnectionStepItem::getArrPlatform() const
{
    return this->mArrival->getPlatform();
}

QString ConnectionStepItem::getMeansOfTransport() const
{
    return this->mJourney->getMeansOfTransport();
}

QString ConnectionStepItem::getDepDelay() const
{
    return this->mDeparture->getDelay();
}

QString ConnectionStepItem::getArrDelay() const
{
    return this->mArrival->getDelay();
}

bool ConnectionStepItem::hasDepDelay() const
{
    return this->mDeparture->hasDelay();
}

bool ConnectionStepItem::hasArrDelay() const
{
    return this->mArrival->hasDelay();
}

bool ConnectionStepItem::hasChangedDeparturePlatform() const
{
    return this->mDeparture->hasChangedPlatform();
}

bool ConnectionStepItem::hasMeansOfTransportation() const
{
    return this->mJourney->hasMeansOfTransportation();
}

int ConnectionStepItem::getUtilisationFirst() const
{
    return this->mDeparture->getUtilisationFirst();
}

int ConnectionStepItem::getUtilisationSecond() const
{
    return this->mDeparture->getUtilisationSecond();
}

double ConnectionStepItem::getDepartureLatitude() const
{
    return this->mDeparture->getLatitude();
}

double ConnectionStepItem::getDepartureLongitude() const
{
    return this->mDeparture->getLongitude();
}

double ConnectionStepItem::getArrivalLatitude() const
{
    return this->mArrival->getLatitude();
}

double ConnectionStepItem::getArrivalLongitude() const
{
    return this->mArrival->getLongitude();
}

bool ConnectionStepItem::hasChangedArrivalPlatform() const
{
    return this->mArrival->hasChangedPlatform();
}
