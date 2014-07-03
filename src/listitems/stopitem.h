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
    bool hasArrTime() const;
    bool hasDepTime() const;
    QDateTime getArrTime() const;
    QDateTime getDepTime() const;
    QString getArrPlatform() const;
    QString getDepPlatform() const;
    QString getArrDelay() const;
    QString getDepDelay() const;

    QString getExternalId();
    QDateTime getTime();
    bool hasDelay();
    bool hasArrDelay();
    bool hasDepDelay();
    bool hasChangedArrPlatform();
    bool hasChangedDepPlatform();
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
    bool mHasDelay;
    bool mHasArrTime;
    bool mHasDepTime;
    bool mHasDepDelay;
    bool mHasArrDelay;
    bool mHasChangedPlatform;
    bool mHasChangedArrPlatform;
    bool mHasChangedDepPlatform;
    QString mPlatform;
    QString mArrPlatform;
    QString mDepPlatform;
    Location *mLocation;
    int mUtilisationFirst;
    int mUtilisationSecond;
    QDateTime mTime;
    QDateTime mArrTime;
    QDateTime mDepTime;
    Duration mDelay;
    Duration mArrDelay;
    Duration mDepDelay;
};

#endif // STOP_H
