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
    ConnectionItem(QDomNode domConnection);
    ~ConnectionItem();

    virtual QVariant data(int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

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
