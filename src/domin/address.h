#ifndef ADDRESS_H
#define ADDRESS_H

#include "location.h"

class QDomNode;

class Address : public Location
{
public:
    Address(QDomNode domAddress);

    inline QString getLongitude();
    inline QString getLatitude();

private:
    QString longitude_;
    QString latitude_;
};

inline QString Address::getLongitude() { return longitude_;}

inline QString Address::getLatitude() { return latitude_;}


#endif // ADDRESS_H
