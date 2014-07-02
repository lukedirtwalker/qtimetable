#ifndef DOMDATE_H
#define DOMDATE_H

#include <QDateTime>

#include "../util/serializable.h"

class DomDate : public Serializable
{
public:
    DomDate();
    DomDate(QDateTime date, bool isArrival);

private:
    virtual void initXMLFields();
};

#endif // DOMDATE_H
