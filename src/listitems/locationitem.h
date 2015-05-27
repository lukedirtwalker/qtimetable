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

#ifndef LOCATIONITEM_H
#define LOCATIONITEM_H

#include "listitem.h"

class QSettings;

class LocationItem : public ListItem
{
    Q_OBJECT

public:
    LocationItem(QObject *parent = nullptr) : ListItem(parent){}
    explicit LocationItem(int dbId, int extId, const QString &name, QString longitude, QString latitude, bool favorite=0, QObject *parent=0);
    explicit LocationItem(int dbId, const QString &extId, const QString &name, QString longitude, QString latitude, bool favorite=false, QObject *parent=0);
    LocationItem(LocationItem* other);
//    LocationItem(SearchItem* other);
//    LocationItem(StationItemGeoAware* other);

    QVariant data(int role) const;
    QHash <int,QByteArray> roleNames() const;
    QString getId() const;

    bool setData(const QVariant &value, int role);

    void saveToSettings(QSettings &settings, const QString &groupKey);
    static QSharedPointer<LocationItem> createFromSettings(const QSettings &settings, const QString &groupKey);

    QString stationName() const;
//    ListItemType getListItemType() const;
    bool favorite()const;
    int dbId() const;
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
    static const QString DATABASE_KEY_;
    static const QString EXTERNAL_ID_KEY_;
    static const QString NAME_KEY_;
    static const QString LATITUDE_KEY_;
    static const QString LONGITUDE_KEY_;
    static const QString TYPE_KEY_;
};

#endif // LOCATIONITEM_H
