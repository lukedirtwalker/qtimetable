#include "station.h"

Station::Station(QDomNode domStation)
{
    this->mType = STATION;

    QDomElement el = domStation.toElement();

    this->mExternalID = el.attributeNode("externalId").value().toLatin1();
    while(this->mExternalID.endsWith( ' ' )) this->mExternalID.chop(1);

    this->mExtStatNR = el.attributeNode("externalStationNr").value().toLatin1();
    while(this->mExtStatNR.endsWith( ' ' )) this->mExtStatNR.chop(1);

    this->mName = el.attributeNode("name").value().toLatin1();
    while(this->mName.endsWith( ' ' )) this->mName.chop(1);

    this->mLatitude = el.attributeNode("y").value().toLatin1();
    while(this->mLatitude.endsWith( ' ' )) this->mLatitude.chop(1);

    this->mLongitude = el.attributeNode("x").value().toLatin1();
    while(this->mLongitude.endsWith( ' ' )) this->mLongitude.chop(1);
}

QString Station::getExtStatNR()
{
    return this->mExtStatNR;
}

QString Station::getLongitude()
{
    return this->mLatitude;
}

QString Station::getLatitude()
{
    return this->mLongitude;
}

QString Station::getExternalID()
{
    return this->mExternalID;
}

QString Station::getScore()
{
    return this->mScore;
}
