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


    QString getPlatform() const;
    int getUtilisationFirst() const;
    int getUtilisationSecond() const;
    double getLatitude() const;
    double getLongitude() const;
    QString getDelay() const;
    QString getName() const;

    QString getExternalId() const;
    inline QDateTime getTime() const;
    bool hasDelay();
    bool hasChangedPlatform();

    void setDateTime(QDateTime t);

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

#endif // STOP_H
