#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QDomDocument>
#include <QMap>

class Serializable
{
public:
    Serializable(QString elemName = "") : domStaticElementName_(elemName) {}

    virtual QDomElement toXML(QDomDocument &query);

protected:
    QString domStaticElementName_;
    QMap<QString, QString> domStaticElementAttributes_;
};

#endif // SERIALIZABLE_H
