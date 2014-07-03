#ifndef TIMETABLEHANDLER_H
#define TIMETABLEHANDLER_H

#include <QObject>
#include <QQmlContext>

#include "../listmodels/resultlistmodel.h"
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
    void depLookupFinished(ResultListType items);
    void arrLookupFinished(ResultListType items);
    void viaLookupFinished(ResultListType items);

private:
    QQmlContext *qmlContext_;

    DatabaseHandler *dbHandler_;

    ResultListModel *depStationModel_, *arrStationModel_, *viaStationModel_;
    LocationItem *depStation_, *arrStation_, *viaStation_;
    SBBConnectionHandler *connHandler;
};

#endif // TIMETABLEHANDLER_H
