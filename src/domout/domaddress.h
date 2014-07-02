#ifndef DOMADDRESS_H
#define DOMADDRESS_H


#include "../util/serializable.h"

class DomAddress : public Serializable
{
public:
    DomAddress(QString name, QString latitude, QString longitude);

private:
    void initXMLFields();
};

#endif // DOMADDRESS_H
