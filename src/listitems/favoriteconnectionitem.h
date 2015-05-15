#ifndef FAVORITECONNECTIONITEM_H
#define FAVORITECONNECTIONITEM_H

#include "listitem.h"
#include "locationitem.h"

class FavoriteConnectionItem : public ListItem
{
    Q_OBJECT
public:
    enum Roles{
        DepStationRole=Qt::UserRole+1,
        ArrStationRole,
        ViaStationRole,
        HasViaStationRole,
        DbIdRole
    };

    FavoriteConnectionItem(QObject *parent = nullptr) : ListItem(parent){}
    explicit FavoriteConnectionItem(const int dbId, const QString &depExtId, const QString &depStation,
                                    const QString &arrExtId, const QString &arrStation, const QString &viaExtId,
                                    const QString &viaStation, QObject *parent = nullptr);
    QVariant data(int role) const;
    QHash <int,QByteArray> roleNames() const;
    bool setData(const QVariant &value, int role);

    QString depStation() const;
    QString arrStation() const;
    QString viaStation() const;
    bool hasViaStation() const;
    QSharedPointer<LocationItem> depStationItem();
    QSharedPointer<LocationItem> arrStationItem();
    QSharedPointer<LocationItem> viaStationItem();
    int dbId() const;

private:
    int dbId_;
    QString depStation_;
    QString arrStation_;
    QString viaStation_;
    bool hasVia_;
    QString depExtId_;
    QString arrExtId_;
    QString viaExtId_;
//    eLocationType mDepLocType;
//    eLocationType mArrLocType;
//    eLocationType mViaLocType;
};

#endif // FAVORITECONNECTIONITEM_H
