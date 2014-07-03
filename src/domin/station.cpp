#include "station.h"

#include <QDomNode>

Station::Station(QDomNode domStation) : Location(STATION)
{
    QDomElement el = domStation.toElement();

    externalID_ = el.attributeNode("externalId").value().trimmed().toLatin1();

    extStatNR_ = el.attributeNode("externalStationNr").value().trimmed().toLatin1();

    name_ = el.attributeNode("name").value().trimmed().toLatin1();

    latitude_ = el.attributeNode("y").value().trimmed().toLatin1();

    longitude_ = el.attributeNode("x").value().trimmed().toLatin1();
}
