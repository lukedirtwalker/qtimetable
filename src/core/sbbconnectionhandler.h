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

    void startConnectionSearch(QSharedPointer<LocationItem> depStation,
                               QSharedPointer<LocationItem> arrStation,
                               QDateTime d, bool isArrival);

    void startConnectionSearch(QSharedPointer<LocationItem> depStation,
                               QSharedPointer<LocationItem> arrStation,
                               QSharedPointer<LocationItem> viaStation,
                               QDateTime d, bool isArrival);

    void searchEarlier();
    void searchLater();
    void stopConnectionSearch();

    inline QList<QSharedPointer<ConnectionItem> > getAvailableConnections();

public slots:
    virtual void parseXMLResponse(QDomDocument xml);
    virtual void parseHTMLResponse(QString html);
    virtual void parseNoTypeResponse(QByteArray data);

private:
    QString searchContext_;
    QList<QSharedPointer<ConnectionItem> > SBBConnections_;
};

inline QList<QSharedPointer<ConnectionItem> > SBBConnectionHandler::getAvailableConnections()
{ return SBBConnections_;}

#endif // SBBCONNECTIONHANDLER_H
