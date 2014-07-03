#ifndef ADDRESS_H
#define ADDRESS_H

#include "location.h"

#include <QDomNode>

class Address : public Location
{
public:
    Address(QDomNode domAddress);

    QString getLongitude();
    QString getLatitude();

private:
    QString mLongitude;
    QString mLatitude;
};

#endif // ADDRESS_H
