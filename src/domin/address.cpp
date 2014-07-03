#include "address.h"

#include <QDomNode>

Address::Address(QDomNode domAddress) : Location(ADDRESS)
{
    QDomElement el = domAddress.toElement();

    name_ = el.attributeNode("name").value().trimmed().toLatin1();

    latitude_ = el.attributeNode("y").value().trimmed().toLatin1();

    longitude_ = el.attributeNode("x").value().trimmed().toLatin1();
}
