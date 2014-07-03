#ifndef DOMDATE_H
#define DOMDATE_H

#include <QDateTime>

#include "../util/serializable.h"

class DomDate : public Serializable
{
public:
    DomDate(QDateTime date, bool isArrival);

};

#endif // DOMDATE_H
