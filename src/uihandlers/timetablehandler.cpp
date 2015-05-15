#include "timetablehandler.h"

#include "../listitems/locationitem.h"
#include "../listmodels/resultlistmodel.h"

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
    if (auto dep = settings_->depStation())
    {
        depStation_ = dep;
        depStationName_ = depStation_->stationName();
        emit depStationChanged();
    }
    if (auto arr = settings_->arrStation())
    {
        arrStation_ = arr;
        arrStationName_ = arrStation_->stationName();
        emit arrStationChanged();
    }
    if (auto via = settings_->viaStation())
    {
        viaStation_ = via;
        viaStationName_ = viaStation_->stationName();
        emit viaStationChanged();
    }

    saveStations_ = settings_->saveStations();
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
                settings_->setDepStation(depStation_);
        } else {
            depStationName_ = "";
            if (saveStations_)
                settings_->setDepStation(QSharedPointer<LocationItem>());
        }
        qDebug() << "dep station changed: " << depStationName_;
        emit depStationChanged();
        break;
    case 1:
        if(!arrStationModel_->isEmpty()) {
            arrStation_ = arrStationModel_->at(index);
            arrStationName_ = arrStation_->stationName();
            if (saveStations_)
                settings_->setArrStation(arrStation_);
        } else {
            arrStationName_ = "";
            if (saveStations_)
                 settings_->setArrStation(QSharedPointer<LocationItem>());
        }
        emit arrStationChanged();
        break;
    case 2:
        if(!viaStationModel_->isEmpty()) {
            viaStation_ = viaStationModel_->at(index);
            viaStationName_ = viaStation_->stationName();
            if (saveStations_)
                settings_->setViaStation(viaStation_);
        } else {
            viaStationName_ = "";
            if (saveStations_)
                 settings_->setViaStation(QSharedPointer<LocationItem>());
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
             settings_->setDepStation(QSharedPointer<LocationItem>());
        emit depStationChanged();
        break;
    case 1:
        arrStation_.clear();
        arrStationName_ = "";
        if (saveStations_)
             settings_->setArrStation(QSharedPointer<LocationItem>());
        emit arrStationChanged();
        break;
    case 2:
        viaStation_.clear();
        viaStationName_ = "";
        if (saveStations_)
             settings_->setViaStation(QSharedPointer<LocationItem>());
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
        QSharedPointer<LocationItem> temp = depStation_;
        depStation_ = arrStation_;
        arrStation_ = temp;
        QString tempName = depStationName_;
        depStationName_ = arrStationName_;
        arrStationName_ = tempName;

        if (saveStations_)
        {
            settings_->setDepStation(depStation_);
            settings_->setArrStation(arrStation_);
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
            connHandler_->startConnectionSearch(depStation_, arrStation_, viaStation_,
                                                timeHandler_->getCurrentDateTime(),
                                                arrival_);
        } else {
            connHandler_->startConnectionSearch(depStation_, arrStation_,
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
        for(auto cur : connections)
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
