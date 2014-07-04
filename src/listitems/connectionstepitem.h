#ifndef CONNECTIONSTEPITEMNEW_H
#define CONNECTIONSTEPITEMNEW_H

#include "stopitem.h"
#include "../domin/journey.h"

class ConnectionStepItem : public ListItem
{
    Q_OBJECT
public:
    ConnectionStepItem(QObject *parent = 0) : ListItem(parent),
    mDeparture{nullptr}, mArrival{nullptr}, mJourney{nullptr} {}
    ConnectionStepItem(QDomNode domConnectionStep, QDateTime date, QObject *parent =0);
    ~ConnectionStepItem();

    QList<StopItem *> getStopovers();

    QVariant data(int role) const;
    QHash<int,QByteArray> roleNames() const;
    QString getId() const;

    QDateTime getDepTime() const;
    QDateTime getArrTime() const;
    QString getDepName() const;
    QString getArrName() const;
    QString getDepPlatform() const;
    QString getArrPlatform() const;
    QString getMeansOfTransport() const;
    QString getDepDelay() const;
    QString getArrDelay() const;
    bool hasDepDelay() const;
    bool hasArrDelay() const;
    bool hasChangedDeparturePlatform() const;
    bool hasChangedArrivalPlatform() const;
    bool hasMeansOfTransportation() const;
    int getUtilisationFirst() const;
    int getUtilisationSecond() const;
    double getDepartureLatitude() const;
    double getDepartureLongitude() const;
    double getArrivalLatitude() const;
    double getArrivalLongitude() const;

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
    StopItem *mDeparture;
    StopItem *mArrival;
    Journey *mJourney;
};

#endif // CONNECTIONSTEPITEMNEW_H
