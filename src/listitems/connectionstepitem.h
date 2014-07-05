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
