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

#ifndef TIMETABLEHANDLER_H
#define TIMETABLEHANDLER_H

#include <QObject>
#include <QQmlContext>

#include "../listmodels/stationlistmodel.h"
#include "../listmodels/connectionlistmodel.h"
#include "../listmodels/connectionstepmodel.h"
#include "../db/db.h"
#include "../core/sbbconnectionhandler.h"

#include "timehandler.h"

class SettingsHandler;
class FavoriteConnectionModel;

class TimeTableHandler : public QObject
{
    Q_OBJECT
public:
    TimeTableHandler(QQmlContext *ctxt, QObject *parent = 0);
    ~TimeTableHandler();

    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

    Q_INVOKABLE void startQuery(const QString &compare, const int type);
    Q_INVOKABLE void setStation(const int index, const int type);
    Q_INVOKABLE void clearStation(const int type);
    Q_INVOKABLE bool switchStations();

    Q_INVOKABLE void lookupConnection();
    Q_INVOKABLE void searchEarlier();
    Q_INVOKABLE void searchLater();

    Q_INVOKABLE inline void setArrival(bool arrival);

    Q_PROPERTY(QString depStation READ depStationName NOTIFY depStationChanged())
    Q_PROPERTY(QString arrStation READ arrStationName NOTIFY arrStationChanged())
    Q_PROPERTY(QString viaStation READ viaStationName NOTIFY viaStationChanged())

    Q_PROPERTY(bool saveStations READ saveStations WRITE setSaveStations NOTIFY saveStationsChanged)

    Q_INVOKABLE QString depStationName() { return depStationName_;}
    Q_INVOKABLE QString arrStationName() { return arrStationName_;}
    Q_INVOKABLE QString viaStationName() { return viaStationName_;}

    bool saveStations() const { return saveStations_; }
    void setSaveStations(bool save);

    bool busy() { return busy_; }

    //FAVORITE CONNECTION
    Q_INVOKABLE void addFavoriteConnection();
    Q_INVOKABLE void modelFavoriteConnections();
    Q_INVOKABLE void setConnectionToFavoriteConnection(const int index);
    Q_INVOKABLE void removeFavoriteConnection(const int dbId);
    Q_INVOKABLE bool isFavoriteConnection() const;


public slots:
    void depLookupFinished(StationListType items);
    void arrLookupFinished(StationListType items);
    void viaLookupFinished(StationListType items);

    void connectionLookedUp(eStatusID id);

signals:
    void depStationChanged();
    void arrStationChanged();
    void viaStationChanged();

    void saveStationsChanged();

    void lookupConnectionError(QString msg);
    void noConnectionsFound();

    void busyChanged();


private:
    QQmlContext *qmlContext_;

    TimeHandler *timeHandler_;

    StationListModel *depStationModel_, *arrStationModel_, *viaStationModel_;
    QSharedPointer<LocationItem> depStation_, arrStation_, viaStation_;
    QString depStationName_, arrStationName_, viaStationName_;

    ConnectionListModel *connections_;

    SBBConnectionHandler *connHandler_;

    SettingsHandler *settings_;

    FavoriteConnectionModel *favoriteConnectionModel_;

    bool arrival_;

    bool saveStations_;
    bool busy_;
};

inline void TimeTableHandler::setArrival(bool arrival) { arrival_ = arrival;}

#endif // TIMETABLEHANDLER_H
