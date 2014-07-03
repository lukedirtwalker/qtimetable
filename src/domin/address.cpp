#include "address.h"

Address::Address(QDomNode domAddress)
{
    this->mType = ADDRESS;

    QDomElement el = domAddress.toElement();

    this->mName = el.attributeNode("name").value().trimmed().toLatin1();
//    while(this->mName.endsWith( ' ' )) this->mName.chop(1);

    this->mLatitude = el.attributeNode("y").value().toLatin1();
    while(this->mLatitude.endsWith( ' ' )) this->mLatitude.chop(1);

    this->mLongitude = el.attributeNode("x").value().toLatin1();
    while(this->mLongitude.endsWith( ' ' )) this->mLongitude.chop(1);
}

QString Address::getLongitude()
{
    return this->mLongitude;
}

QString Address::getLatitude()
{
    return this->mLatitude;
}
