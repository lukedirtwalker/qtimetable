#include "favoriteconnectionitem.h"

#include <QtCore/QSharedPointer>

FavoriteConnectionItem::FavoriteConnectionItem(const int dbId, const QString &depExtId,
                                               const QString &depStation, const QString &arrExtId,
                                               const QString &arrStation, const QString &viaExtId,
                                               const QString &viaStation, QObject *parent)
 : ListItem(parent), dbId_(dbId), depStation_(depStation), arrStation_(arrStation), depExtId_(depExtId), arrExtId_(arrExtId)
{
    hasVia_ = !viaExtId.isEmpty();
    viaExtId_ = viaExtId;
    viaStation_ = viaStation;
}

QVariant FavoriteConnectionItem::data(int role) const
{
    switch(role)
    {
    case DepStationRole:
        return depStation();
    case ArrStationRole:
        return arrStation();
    case ViaStationRole:
        return viaStation();
    case HasViaStationRole:
        return hasViaStation();
    case DbIdRole:
        return dbId();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> FavoriteConnectionItem::roleNames() const
{
    QHash <int,QByteArray> names;
    names[DepStationRole] = "DepStation";
    names[ArrStationRole] = "ArrStation";
    names[ViaStationRole] = "ViaStation";
    names[HasViaStationRole] = "HasViaStation";
    names[DbIdRole] = "DbId";
    return names;
}

bool FavoriteConnectionItem::setData(const QVariant &, int )
{
    return false;
}

QString FavoriteConnectionItem::depStation() const
{
   return depStation_;
}

QString FavoriteConnectionItem::arrStation() const
{
    return arrStation_;
}

QString FavoriteConnectionItem::viaStation() const
{
    return viaStation_;
}

bool FavoriteConnectionItem::hasViaStation() const
{
    return hasVia_;
}

QSharedPointer<LocationItem> FavoriteConnectionItem::depStationItem()
{
    return QSharedPointer<LocationItem>::create(-1, depExtId_, depStation_, "", "", false);
}

QSharedPointer<LocationItem> FavoriteConnectionItem::arrStationItem()
{
    return QSharedPointer<LocationItem>::create(-1, arrExtId_, arrStation_, "", "", false);
}

QSharedPointer<LocationItem> FavoriteConnectionItem::viaStationItem()
{
    return QSharedPointer<LocationItem>::create(-1, viaExtId_, viaStation_, "", "", false);
}

int FavoriteConnectionItem::dbId() const
{
    return dbId_;
}
