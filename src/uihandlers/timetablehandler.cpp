#include "timetablehandler.h"

#include "../listitems/locationitem.h"
#include "../listmodels/resultlistmodel.h"


TimeTableHandler::TimeTableHandler(QQmlContext *ctxt,
                                   DatabaseHandler *dbHandler, QObject *parent)
    : QObject(parent), qmlContext_(ctxt),
      dbHandler_(dbHandler), queryHandler_{nullptr}, depStation_{},
      arrStation_{}, viaStation_{}
{
    depStationModel_ = new ResultListModel(new LocationItem());
    arrStationModel_ = new ResultListModel(new LocationItem());
    viaStationModel_ = new ResultListModel(new LocationItem());

    qmlContext_->setContextProperty("depStationModel", depStationModel_);
    qmlContext_->setContextProperty("arrStationModel", arrStationModel_);
    qmlContext_->setContextProperty("viaStationModel", viaStationModel_);

    connHandler = new SBBConnectionHandler();
}

void TimeTableHandler::startQuery(const QString &compare, const int type)
{
    if(compare.isEmpty())
        return;
//    if(queryHandler_) {
//        qDebug() << "Existing query handler";
//        delete queryHandler_;
//    }
//    queryThread_ = new QThread();
//    queryHandler_ = new ThreadedDbHandler(dbHandler_->getDb(), compare);
//    connect(queryThread_, &QThread::started, queryHandler_,
//            &ThreadedDbHandler::run);

//    // TODO from QT 5.2 we propably can use lambda like this:
//    // connect(queryHandler_, &ThreadedDbHandler::finished, this,
//    // [this](ResultListType items) {this->depStationModel_->appendRows(items);});

//    switch(type) {
//    case 0: // dep
//        depStationModel_->clear();
//        connect(queryHandler_, &ThreadedDbHandler::finished, this,
//                &TimeTableHandler::depLookupFinished);
//        break;
//    case 1: // arr
//        arrStationModel_->clear();
//        connect(queryHandler_, &ThreadedDbHandler::finished, this,
//                &TimeTableHandler::arrLookupFinished);
//        break;
//    case 2: // via
//        viaStationModel_->clear();
//        connect(queryHandler_, &ThreadedDbHandler::finished, this,
//                &TimeTableHandler::viaLookupFinished);
//        break;
//    default:
//        qDebug() << "Unsupported type" << type;
//        break;
//    }
//    connect(queryThread_, &QThread::finished, queryHandler_,
//            &ThreadedDbHandler::deleteLater);
//    connect(queryThread_, &QThread::finished, queryThread_,
//            &QThread::deleteLater);
//    //start the query
//    queryHandler_->moveToThread(queryThread_);
//    queryThread_->start();
}

void TimeTableHandler::setStation(int index, int type)
{
    qDebug() << "setStation" << type << index;
    // TODO either use dynamic_cast or use templated model
    switch(type) {
    case 0:
        depStation_ = dynamic_cast<LocationItem*>(depStationModel_->at(index));
        qDebug() << depStation_->stationName();
        break;
    case 1:
        arrStation_ = dynamic_cast<LocationItem*>(arrStationModel_->at(index));
        break;
    case 2:
        viaStation_ = dynamic_cast<LocationItem*>(viaStationModel_->at(index));
        break;
    default:
        qDebug() << "Unsupported type" << type;
        break;
    }
}

void TimeTableHandler::lookupConnection()
{
    // TODO
    if(depStation_ && arrStation_) {
        connHandler->startConnectionSearch(depStation_, arrStation_, QDateTime::currentDateTime(), false);
    }
}

void TimeTableHandler::depLookupFinished(ResultListType items)
{
    depStationModel_->appendRows(items);
}

void TimeTableHandler::arrLookupFinished(ResultListType items)
{
    arrStationModel_->appendRows(items);
}

void TimeTableHandler::viaLookupFinished(ResultListType items)
{
    viaStationModel_->appendRows(items);
}
