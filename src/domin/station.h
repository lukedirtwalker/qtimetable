#ifndef STATION_H
#define STATION_H

#include "location.h"

#include <QDomNode>

class Station : public Location
{
public:
    Station(QDomNode domStation);

    QString getLongitude();
    QString getLatitude();
    QString getExtStatNR();
    QString getExternalID();
    QString getScore();

private:
    QString mExternalID;
    QString mScore;
    QString mLatitude;
    QString mLongitude;
    QString mExtStatNR;
};

#endif // STATION_H
