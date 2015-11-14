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

#include "timetablehandler.h"

#include "../listitems/locationitem.h"
#include "../listmodels/resultlistmodel.h"
#include "../listmodels/favoriteconnectionmodel.h"

#include "../util/settingshandler.h"

TimeTableHandler::TimeTableHandler(QQmlContext *ctxt, QObject *parent)
    : QObject(parent), qmlContext_(ctxt),
      depStation_{}, arrStation_{}, viaStation_{}, arrival_{false}, busy_{false}
{
    timeHandler_ = new TimeHandler(this);
    qmlContext_->setContextProperty("timeHandler", timeHandler_);

    depStationModel_ = new StationListModel(this);
    arrStationModel_ = new StationListModel(this);
    viaStationModel_ = new StationListModel(this);

    qmlContext_->setContextProperty("depStationModel", depStationModel_);
    qmlContext_->setContextProperty("arrStationModel", arrStationModel_);
    qmlContext_->setContextProperty("viaStationModel", viaStationModel_);

    connections_ = new ConnectionListModel(this);

    qmlContext_->setContextProperty("connectionModel", connections_);

    connHandler_ = new SBBConnectionHandler(this);
    connect(connHandler_, &SBBConnectionHandler::parsingFinished,
            this, &TimeTableHandler::connectionLookedUp);

    // settings
    settings_ = new SettingsHandler();
    if (depStation_ = settings_->depStation())
    {
        depStationName_ = depStation_->stationName();
        emit depStationChanged();
    }
    if (arrStation_ = settings_->arrStation())
    {
        arrStationName_ = arrStation_->stationName();
        emit arrStationChanged();
    }
    if (viaStation_ = settings_->viaStation())
    {
        viaStationName_ = viaStation_->stationName();
        emit viaStationChanged();
    }

    saveStations_ = settings_->saveStations();

    favoriteConnectionModel_ = new FavoriteConnectionModel(this);
    qmlContext_->setContextProperty("favoritesModel", favoriteConnectionModel_);
}

TimeTableHandler::~TimeTableHandler()
{
    depStationModel_->clear();
    arrStationModel_->clear();
    viaStationModel_->clear();
    connections_->clear();

    delete settings_;
}

void TimeTableHandler::startQuery(const QString &compare, const int type)
{
    if(compare.isEmpty())
        return;
    QThread *queryThread = new QThread();
    ThreadedDbHandler *queryHandler = new ThreadedDbHandler(compare);
    connect(queryThread, &QThread::started, queryHandler,
            &ThreadedDbHandler::run);

    // TODO from QT 5.2 we propably can use lambda like this:
    // connect(queryHandler_, &ThreadedDbHandler::finished, this,
    // [this](ResultListType items) {this->depStationModel_->appendRows(items);});

    switch(type) {
    case 0: // dep
        connect(queryHandler, &ThreadedDbHandler::foundResults, this,
                &TimeTableHandler::depLookupFinished);
        break;
    case 1: // arr
        connect(queryHandler, &ThreadedDbHandler::foundResults, this,
                &TimeTableHandler::arrLookupFinished);
        break;
    case 2: // via
        connect(queryHandler, &ThreadedDbHandler::foundResults, this,
                &TimeTableHandler::viaLookupFinished);
        break;
    default:
        qDebug() << "Unsupported type" << type;
        break;
    }
    connect(queryHandler, &ThreadedDbHandler::finished, queryThread,
            &QThread::quit);
    connect(queryHandler, &ThreadedDbHandler::finished, queryHandler,
            &ThreadedDbHandler::deleteLater);
    connect(queryThread, &QThread::finished, queryThread,
            &QThread::deleteLater);
    //start the query
    queryHandler->moveToThread(queryThread);
    queryThread->start();
}

void TimeTableHandler::setStation(int index, int type)
{
    switch(type) {
    case 0:
        if(!depStationModel_->isEmpty()) {
            depStation_ = depStationModel_->at(index);
            depStationName_ = depStation_->stationName();
            if (saveStations_)
                settings_->setDepStation(depStation_.data());
        } else {
            depStationName_ = "";
            if (saveStations_)
                settings_->setDepStation(nullptr);
        }
        qDebug() << "dep station changed: " << depStationName_;
        emit depStationChanged();
        break;
    case 1:
        if(!arrStationModel_->isEmpty()) {
            arrStation_ = arrStationModel_->at(index);
            arrStationName_ = arrStation_->stationName();
            if (saveStations_)
                settings_->setArrStation(arrStation_.data());
        } else {
            arrStationName_ = "";
            if (saveStations_)
                 settings_->setArrStation(nullptr);
        }
        emit arrStationChanged();
        break;
    case 2:
        if(!viaStationModel_->isEmpty()) {
            viaStation_ = viaStationModel_->at(index);
            viaStationName_ = viaStation_->stationName();
            if (saveStations_)
                settings_->setViaStation(viaStation_.data());
        } else {
            viaStationName_ = "";
            if (saveStations_)
                 settings_->setViaStation(nullptr);
        }
        emit viaStationChanged();
        break;
    default:
        qDebug() << "Unsupported type" << type;
    }
}

void TimeTableHandler::clearStation(int type)
{
    switch(type) {
    case 0:
        depStation_.clear();
        depStationName_ = "";
        if (saveStations_)
             settings_->setDepStation(nullptr);
        emit depStationChanged();
        break;
    case 1:
        arrStation_.clear();
        arrStationName_ = "";
        if (saveStations_)
             settings_->setArrStation(nullptr);
        emit arrStationChanged();
        break;
    case 2:
        viaStation_.clear();
        viaStationName_ = "";
        if (saveStations_)
             settings_->setViaStation(nullptr);
        emit viaStationChanged();
        break;
    default:
        qDebug() << "Unsupported type" << type;
        break;
    }
}

bool TimeTableHandler::switchStations()
{
    if(depStation_ || arrStation_) {
        depStationModel_->clear();
        arrStationModel_->clear();

        std::swap(depStation_, arrStation_);
        std::swap(depStationName_, arrStationName_);

        if (saveStations_)
        {
            settings_->setDepStation(depStation_.data());
            settings_->setArrStation(arrStation_.data());
        }

        emit depStationChanged();
        emit arrStationChanged();
        return true;
    }
    return false;
}

void TimeTableHandler::lookupConnection()
{
    connections_->clear();
    // TODO
    if(depStation_ && arrStation_) {
        if(viaStation_) {
            connHandler_->startConnectionSearch(depStation_.data(), arrStation_.data(), viaStation_.data(),
                                                timeHandler_->getCurrentDateTime(),
                                                arrival_);
        } else {
            connHandler_->startConnectionSearch(depStation_.data(), arrStation_.data(),
                                                timeHandler_->getCurrentDateTime(),
                                                arrival_);
        }
        busy_ = true;
        emit busyChanged();
    }
}

void TimeTableHandler::searchEarlier()
{
    busy_ = true;
    emit busyChanged();
    connHandler_->searchEarlier();
}

void TimeTableHandler::searchLater()
{
    busy_ = true;
    emit busyChanged();
    connHandler_->searchLater();
}

void TimeTableHandler::depLookupFinished(StationListType items)
{
    depStationModel_->replaceData(items);
}

void TimeTableHandler::arrLookupFinished(StationListType items)
{
    arrStationModel_->replaceData(items);
}

void TimeTableHandler::viaLookupFinished(StationListType items)
{
    viaStationModel_->replaceData(items);
}

void TimeTableHandler::connectionLookedUp(eStatusID id)
{
    busy_ = false;
    emit busyChanged();
    if(XML_ERROR_RESPONSE == id || HTML_ERROR_RESPONSE == id)
    {
        QString msg = connHandler_->getErrorMessage();
        qDebug() << "Connection lookup error" << msg;
        emit lookupConnectionError(msg);
    }
    else if(NO_CONNECTIONS_RESPONSE == id)
    {
        qDebug() << "Connection lookup no connections found";
        emit noConnectionsFound();
    }
    else
    {

        QList<QSharedPointer<ConnectionItem> > connections = connHandler_->getAvailableConnections();
        for(auto& cur : connections)
        {
            if(cur->hasConnectionStateInformation())
                cur->setConnectionStateInfo(1);
            else
                cur->setConnectionStateInfo(0);
        }
        connections_->replaceData(connections);
    }
}

void TimeTableHandler::setSaveStations(bool save)
{
    saveStations_ = save;
    settings_->setSaveStations(save);
    emit saveStationsChanged();
}

bool TimeTableHandler::showWalkInDepTime() const
{
    return settings_->showWalkInDepTime();
}

void TimeTableHandler::setShowWalkInDepTime(bool show)
{
    settings_->setShowWalkInDepTime(show);
    emit showWalkInDepTimeChanged();
}

void TimeTableHandler::addFavoriteConnection()
{
    QVariant id = DatabaseHandler::getInstance().saveFavoriteConnection(depStation_, arrStation_, viaStation_);
    if (id.isValid())
    {
        QString viaExtId = viaStation_ ? viaStation_->getExternalId() : "";
        QString viaName = viaStation_ ? viaStation_->stationName() : "";
        favoriteConnectionModel_->appendRow(QSharedPointer<FavoriteConnectionItem>::create(id.toInt(),
                                                                   depStation_->getExternalId(), depStation_->stationName(),
                                                                   arrStation_->getExternalId(), arrStation_->stationName(),
                                                                   viaExtId, viaName));
    }
    else
    {
        modelFavoriteConnections();
    }
}

void TimeTableHandler::modelFavoriteConnections()
{
    favoriteConnectionModel_->clear();
    DatabaseHandler::getInstance().populateFavoritesConnections(favoriteConnectionModel_);
}

void TimeTableHandler::setConnectionToFavoriteConnection(int index)
{
    auto favoriteItem = favoriteConnectionModel_->at(index);
    depStation_ = favoriteItem->depStationItem();
    depStationName_ = depStation_->stationName();
    arrStation_ = favoriteItem->arrStationItem();
    arrStationName_ = arrStation_->stationName();

    if (saveStations_)
    {
        settings_->setDepStation(depStation_.data());
        settings_->setArrStation(arrStation_.data());
    }

    emit depStationChanged();
    emit arrStationChanged();
}

void TimeTableHandler::removeFavoriteConnection(int dbId)
{
    DatabaseHandler::getInstance().removeFavoriteConnection(dbId);
    int idx = -1;
    for (int i = 0; i < favoriteConnectionModel_->rowCount() && idx == -1; ++i)
        if (favoriteConnectionModel_->at(i)->dbId() == dbId) idx = i;
    if (idx != -1) favoriteConnectionModel_->removeRow(idx);
}

bool TimeTableHandler::isFavoriteConnection() const
{
    return DatabaseHandler::getInstance().isFavoriteConnection(depStation_, arrStation_, viaStation_);
}
