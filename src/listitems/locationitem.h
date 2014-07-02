#ifndef LOCATIONITEM_H
#define LOCATIONITEM_H

#include "listitem.h"

class LocationItem : public ListItem
{
    Q_OBJECT

public:
    LocationItem(QObject *parent = nullptr) : ListItem(parent){}
    explicit LocationItem(int dbId, int extId, const QString &name, QString longitude, QString latitude, bool favorite=0, QObject *parent=0);
    explicit LocationItem(int dbId, const QString &extId, const QString &name, QString longitude, QString latitude, bool favorite, QObject *parent=0);
    LocationItem(LocationItem* other);
//    LocationItem(SearchItem* other);
//    LocationItem(StationItemGeoAware* other);

    QVariant data(int role) const;
    QHash <int,QByteArray> roleNames() const;
    QString getId() const;

    QString stationName() const;
//    ListItemType getListItemType() const;
    bool favorite()const;
    int getDbId() const;
    int getExtId() const;
    QString getExternalId() const;
    void setFavorite(bool fav);
    bool operator <(const LocationItem &other) const;
//    eLocationType getLocationType() const;
    QString getLatitude() const;
    QString getLongitude() const;

    enum Roles{
        StationNameRole = Qt::UserRole+1,
        TypeRole,
        LocationTypeRole,
        FavoriteRole
    };

private:
    int dbId_;
    int externalId_;
    bool favorite_;
    QString locationName_;
    QString extIdString_;
    QString latitude_;
    QString longitude_;
//    ListItemType mType;
//    eLocationType mLocationType;
};

#endif // LOCATIONITEM_H
