#include "serializable.h"

QDomElement Serializable::toXML(QDomDocument &query)
{
    QDomElement el = query.createElement(domStaticElementName_);
    for (auto it = domStaticElementAttributes_.begin();
         it != domStaticElementAttributes_.end();it++)
        el.setAttribute(it.key(),it.value());
    return el;
}
