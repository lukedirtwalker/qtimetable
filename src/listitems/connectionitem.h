#ifndef CONNECTIONITEMNEW_H
#define CONNECTIONITEMNEW_H

#include "listitem.h"
#include "../util/duration.h"
#include "../util/globalshared.h"
#include "connectionstepitem.h"

class QDomNode;

class ConnectionItem : public ListItem
{
    Q_OBJECT
public:
    ConnectionItem(QObject *parent = 0) : ListItem(parent) {}
    ConnectionItem(QDomNode domConnection);
    ~ConnectionItem();

    QList<ConnectionStepItem *> getConnectionSteps();
    QVector<eConnectionStateInformation> getConnectionStateInformations();
    void setConnectionStateInfo(int info);
    bool hasConnectionStateInformation();

    virtual QVariant data(int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual QString getId() const;

    QDateTime getDepartureTime() const;
    QDateTime getArrivalTime() const;
    QString getDuration() const;
    QString getPlatform() const;
    int getConnectionStateInfo() const;
    int getNumberOfChanges() const;
    int getUtilisationFirst() const;
    int getUtilisationSecond() const;
    bool hasChangedDeparturePlatform() const;

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

    bool mHasChangedDeparturePlatform;
    bool mHasIrregularServiceDays;
    bool mHasCSInformation;
    QString mPlatform;
    QString mServiceDays;
    QString mId;
    QDateTime mDate;
    QDateTime mDepartureTime;
    QDateTime mArrivalTime;
    Duration mDuration;
    int mNrChanges;
    int mUtilisationFirst;
    int mUtilisationSecond;

    QVector<QString> mConnectionVehicles;
    QVector<eConnectionStateInformation> mConnectionStateInformations;
    QList<ConnectionStepItem*> mConnectionSteps;

    int mConnectionStateInfo;
};

#endif // CONNECTIONITEMNEW_H
