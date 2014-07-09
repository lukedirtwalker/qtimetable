#include "timetablehandler.h"

#include "../listitems/locationitem.h"
#include "../listmodels/resultlistmodel.h"


TimeTableHandler::TimeTableHandler(QQmlContext *ctxt, QObject *parent)
    : QObject(parent), qmlContext_(ctxt),
      depStation_{}, arrStation_{}, viaStation_{}, arrival_{false}
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
}

TimeTableHandler::~TimeTableHandler()
{
    depStationModel_->clear();
    arrStationModel_->clear();
    viaStationModel_->clear();
    connections_->clear();
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
        depStation_ = depStationModel_->at(index);
        qDebug() << depStation_->stationName();
        break;
    case 1:
        arrStation_ = arrStationModel_->at(index);
        break;
    case 2:
        viaStation_ = viaStationModel_->at(index);
        break;
    default:
        qDebug() << "Unsupported type" << type;
        break;
    }
}

void TimeTableHandler::lookupConnection()
{
    connections_->clear();
    // TODO
    if(depStation_ && arrStation_) {
        connHandler_->startConnectionSearch(depStation_, arrStation_,
                                            timeHandler_->getCurrentDateTime(),
                                            arrival_);
    }
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
    if(XML_ERROR_RESPONSE == id || HTML_ERROR_RESPONSE == id)
    {
        QString msg = connHandler_->getErrorMessage();
//        TODO emit lookupConnectionError(msg);
    }
    else if(NO_CONNECTIONS_RESPONSE == id)
    {
//      TODO   emit this->noConnectionsFound();
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
