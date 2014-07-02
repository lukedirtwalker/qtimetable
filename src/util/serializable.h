#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QDomDocument>
#include <QMap>

class Serializable
{
public:
    Serializable() {}

    virtual QDomElement toXML(QDomDocument &query);

protected:
    virtual void initXMLFields() = 0;

    QString domStaticElementName_;
    QMap<QString, QString> domStaticElementAttributes_;
};

#endif // SERIALIZABLE_H
