#ifndef TIMETABLEHANDLER_H
#define TIMETABLEHANDLER_H

#include <QObject>
#include <QQmlContext>

#include "../listmodels/stationlistmodel.h"
#include "../db/db.h"
#include "../core/sbbconnectionhandler.h"

class TimeTableHandler : public QObject
{
    Q_OBJECT
public:
    TimeTableHandler(QQmlContext *ctxt,
                     DatabaseHandler *dbHandler, QObject *parent = 0);

    Q_INVOKABLE void startQuery(const QString &compare, const int type);
    Q_INVOKABLE void setStation(const int index, const int type);

    Q_INVOKABLE void lookupConnection();

public slots:
    void depLookupFinished(StationListType items);
    void arrLookupFinished(StationListType items);
    void viaLookupFinished(StationListType items);

private:
    QQmlContext *qmlContext_;

    DatabaseHandler *dbHandler_;

    StationListModel *depStationModel_, *arrStationModel_, *viaStationModel_;
    LocationItem *depStation_, *arrStation_, *viaStation_;
    SBBConnectionHandler *connHandler;
};

#endif // TIMETABLEHANDLER_H
