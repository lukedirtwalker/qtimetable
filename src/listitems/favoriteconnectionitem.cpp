/******************************************************************************
*Copyright (c) 2013-2015, Lukas Vogel, Stefan Willi
*All rights reserved.
*
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions are met:
*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*    * Neither the name of the <organization> nor the
*      names of its contributors may be used to endorse or promote products
*      derived from this software without specific prior written permission.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
*DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

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
