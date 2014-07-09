#include "locationitem.h"

#include <QDebug>

LocationItem::LocationItem(int dbId, int extId, const QString &name, QString longitude, QString latitude, bool favorite, QObject *parent)
    : ListItem(parent)
{
    dbId_ = dbId;
    externalId_ = extId;
    QString tmp;
    tmp.sprintf("%05d",extId);
    extIdString_ = QString("0085%1#85").arg(tmp);
    locationName_ = name;
    favorite_ = favorite;
    longitude_ = longitude;
    latitude_ = latitude;
}

LocationItem::LocationItem(int dbId, const QString &extId, const QString &name, QString longitude, QString latitude, bool favorite, QObject *parent)
    : ListItem(parent)
{
    dbId_ = dbId;
    externalId_ = 0;
    if(extId.isEmpty())
    {
        externalId_ = -1;
    }
    extIdString_ = extId;
    locationName_ = name;
    favorite_ = favorite;
    longitude_ = longitude;
    latitude_ = latitude;
}

LocationItem::LocationItem(LocationItem *other)
    : ListItem(other->parent())
{
    dbId_ = other->getDbId();
    externalId_ = other->getExtId();
    extIdString_ = other->getExternalId();
    locationName_ = other->stationName();
    favorite_ = other->favorite();
    latitude_ = other->getLatitude();
    longitude_ = other->getLongitude();
}

//LocationItem::LocationItem(SearchItem *other)
//    : ListItem(other->parent())
//{
//    mDbId = -1;
//    mExternalId = -1;
//    mLocationName = other->SearchText();
//    mFavorite = false;
//    mLocationType = UNDEFINED;
//    mType = other->Type();
//}

//LocationItem::LocationItem(StationItemGeoAware *other)
//    : ListItem(other->parent())
//{
//    mDbId = other->getDbId();
//    mExternalId = other->getExtId();
//    mExtIdString = other->getExternalId();
//    mLocationName = other->StationName();
//    mFavorite = other->Favorite();
//    mLocationType = STATION;
//    mType = other->Type();
//}

QHash<int,QByteArray> LocationItem::roleNames() const
{
    QHash<int,QByteArray> names;
    names[StationNameRole] = "stationName";
    names[FavoriteRole] = "favorite";
//    names[role++] = "Type";
//    names[LocationTypeRole] = "LocType";
    return names;
}

QVariant LocationItem::data(int role) const
{
    switch(role)
    {
    case StationNameRole:
        return stationName();
    case FavoriteRole:
        return favorite();
//    case TypeRole:
//        return getListItemType();
//    case LocationTypeRole:
//        return getLocationType();
    default:
        return QVariant();
    }
}

QString LocationItem::getId() const
{
    return locationName_;
}

bool LocationItem::setData(const QVariant &value, int role)
{
    switch(role)
    {
    case StationNameRole:
        return false;
    case FavoriteRole:
        favorite_ = value.toBool();
        return true;
//    case TypeRole:
//        return getListItemType();
//    case LocationTypeRole:
//        return getLocationType();
    default:
        return false;
    }
}

QString LocationItem::stationName() const
{
    return locationName_;
}

//ListItemType LocationItem::getListItemType() const
//{
//    return mType;
//}

bool LocationItem::favorite() const
{
    return favorite_;
}

int LocationItem::getDbId() const
{
    return dbId_;
}

int LocationItem::getExtId() const
{
    return externalId_;
}

QString LocationItem::getExternalId() const
{
    return extIdString_;
}

void LocationItem::setFavorite(bool fav)
{
    favorite_ = fav;
}

bool LocationItem::operator <(const LocationItem &other) const
{
    return (favorite() > other.favorite());
}

//eLocationType LocationItem::getLocationType() const
//{
//    return mLocationType;
//}

QString LocationItem::getLatitude() const
{
    return this->latitude_;
}

QString LocationItem::getLongitude() const
{
    return this->longitude_;
}
