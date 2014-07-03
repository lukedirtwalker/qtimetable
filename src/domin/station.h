#ifndef STATION_H
#define STATION_H

#include "location.h"

class QDomNode;

class Station : public Location
{
public:
    Station(QDomNode domStation);

    inline QString getLongitude();
    inline QString getLatitude();
    inline QString getExtStatNR();
    inline QString getExternalID();
    inline QString getScore();

private:
    QString externalID_;
    QString score_;
    QString latitude_;
    QString longitude_;
    QString extStatNR_;
};

inline QString Station::getExtStatNR() { return extStatNR_;}

inline QString Station::getLongitude() { return latitude_;}

inline QString Station::getLatitude() { return longitude_;}

inline QString Station::getExternalID() { return externalID_;}

inline QString Station::getScore() { return score_;}

#endif // STATION_H
