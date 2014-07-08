#ifndef SBBCONNECTIONHANDLER_H
#define SBBCONNECTIONHANDLER_H

#include "../listitems/connectionitem.h"
#include "sbbhandler.h"

class LocationItem;

class SBBConnectionHandler : public SBBHandler
{
    Q_OBJECT
public:
    SBBConnectionHandler(QObject *parent = nullptr) : SBBHandler(parent) {}

    void startConnectionSearch(LocationItem *depStation, LocationItem *arrStation, QDateTime d, bool isArrival);

    void startConnectionSearch(LocationItem *depStation, LocationItem *arrStation, LocationItem* viaStation,
                               QDateTime d, bool isArrival);

    void searchEarlier();
    void searchLater();
    void stopConnectionSearch();

    inline QList<ConnectionItem*> getAvailableConnections();

public slots:
    virtual void parseXMLResponse(QDomDocument xml);
    virtual void parseHTMLResponse(QString html);
    virtual void parseNoTypeResponse(QByteArray data);

private:
    QString searchContext_;
    QList<ConnectionItem*> SBBConnections_;
};

inline QList<ConnectionItem*> SBBConnectionHandler::getAvailableConnections()
{ return SBBConnections_;}

#endif // SBBCONNECTIONHANDLER_H
