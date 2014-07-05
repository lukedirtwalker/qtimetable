#ifndef STOPITEM_H
#define STOPITEM_H

#include "../domin/location.h"
#include "../util/duration.h"
#include "listitem.h"

#include <QDomNode>
#include <QDateTime>

class StopItem : public ListItem
{
    Q_OBJECT
public:
    StopItem(QObject *parent = 0) : ListItem(parent){}
    StopItem(QDomNode domBasicStop,QDateTime date);
    ~StopItem();

    virtual QString getId() const;
    virtual QVariant data(int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    double getLatitude() const;
    double getLongitude() const;
    QString getExternalId() const;

    inline QString getPlatform() const;
    inline int getUtilisationFirst() const;
    inline int getUtilisationSecond() const;
    inline QString getDelay() const;
    inline QString getName() const;
    inline QDateTime getTime() const;
    inline bool hasDelay() const;
    inline bool hasChangedPlatform() const;

    inline void setDateTime(QDateTime t);

    enum Roles{StationRole=Qt::UserRole+1,
               PlatformRole,
               ArrivalTimeRole,
               DepartureTimeRole,
               UtilisationFirstRole,
               UtilisationSecondRole,
               HasArrivalTimeRole,
               HasDepartureTimeRole
              };


private:
    bool hasDelay_;
    bool hasArrTime_;
    bool hasDepTime_;
    bool hasDepDelay_;
    bool hasArrDelay_;
    bool hasChangedPlatform_;
    bool hasChangedArrPlatform_;
    bool hasChangedDepPlatform_;
    QString platform_;
    QString arrPlatform_;
    QString depPlatform_;
    Location *location_;
    int utilisationFirst_;
    int utilisationSecond_;
    QDateTime time_;
    QDateTime arrTime_;
    QDateTime depTime_;
    Duration delay_;
};

inline QDateTime StopItem::getTime() const { return time_;}

inline QString StopItem::getPlatform() const { return platform_;}

inline int StopItem::getUtilisationFirst() const { return utilisationFirst_;}

inline int StopItem::getUtilisationSecond() const { return utilisationSecond_;}

inline QString StopItem::getDelay() const { return delay_.toString();}

inline QString StopItem::getName() const { return location_->getName();}

inline bool StopItem::hasDelay() const { return hasDelay_;}

inline bool StopItem::hasChangedPlatform() const { return hasChangedPlatform_;}

inline void StopItem::setDateTime(QDateTime t) { time_ = t;}

#endif // STOP_H
