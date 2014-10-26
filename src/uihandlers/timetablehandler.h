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

class TimeTableHandler : public QObject
{
    Q_OBJECT
public:
    TimeTableHandler(QQmlContext *ctxt, QObject *parent = 0);
    ~TimeTableHandler();

    Q_INVOKABLE void startQuery(const QString &compare, const int type);
    Q_INVOKABLE void setStation(const int index, const int type);
    Q_INVOKABLE void clearStation(const int type);
    Q_INVOKABLE bool switchStations();

    Q_INVOKABLE void lookupConnection();

    Q_INVOKABLE inline void setArrival(bool arrival);

    Q_PROPERTY(QString depStation READ depStationName NOTIFY depStationChanged())
    Q_PROPERTY(QString arrStation READ arrStationName NOTIFY arrStationChanged())
    Q_PROPERTY(QString viaStation READ viaStationName NOTIFY viaStationChanged())

    Q_INVOKABLE QString depStationName() { return depStationName_;}
    Q_INVOKABLE QString arrStationName() { return arrStationName_;}
    Q_INVOKABLE QString viaStationName() { return viaStationName_;}


public slots:
    void depLookupFinished(StationListType items);
    void arrLookupFinished(StationListType items);
    void viaLookupFinished(StationListType items);

    void connectionLookedUp(eStatusID id);

signals:
    void depStationChanged();
    void arrStationChanged();
    void viaStationChanged();


private:
    QQmlContext *qmlContext_;

    TimeHandler *timeHandler_;

    StationListModel *depStationModel_, *arrStationModel_, *viaStationModel_;
    QSharedPointer<LocationItem> depStation_, arrStation_, viaStation_;
    QString depStationName_, arrStationName_, viaStationName_;

    ConnectionListModel *connections_;

    SBBConnectionHandler *connHandler_;

    bool arrival_;
};

inline void TimeTableHandler::setArrival(bool arrival) { arrival_ = arrival;}

#endif // TIMETABLEHANDLER_H
