#ifndef SBBCONNECTIONHANDLER_H
#define SBBCONNECTIONHANDLER_H

#include "../listitems/connectionitem.h"
#include "sbbhandler.h"

class LocationItem;

class SBBConnectionHandler : public SBBHandler
{
    Q_OBJECT
public:
    SBBConnectionHandler();

    void startConnectionSearch(LocationItem *depStation, LocationItem *arrStation, QDateTime d, bool isArrival);

    void startConnectionSearch(QString startName, QString startExternalId, QString startLatitude, QString startLongitude,
                               QString destName, QString destExternalId, QString destLatitude, QString destLongitude,
                               QString viaName, QString viaExternalId, QString viaLatitude, QString viaLongitude,
                               QDateTime d, bool isArrival);

    void startConnectionSearch(QString startName, QString startExternalId, QString startLatitude, QString startLongitude,
                               QString destName, QString destExternalId, QString destLatitude, QString destLongitude,
                               QDateTime d, bool isArrival);
    void searchEarlier();
    void searchLater();
    void stopConnectionSearch();

    QList<ConnectionItem*> getAvailableConnections();

public slots:
    virtual void parseXMLResponse(QDomDocument xml);
    virtual void parseHTMLResponse(QString html);
    virtual void parseNoTypeResponse(QByteArray data);

private:
    QString mSearchContext;
    QList<ConnectionItem*> mSBBConnections;
};

#endif // SBBCONNECTIONHANDLER_H
