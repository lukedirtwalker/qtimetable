#ifndef FLAGS_H
#define FLAGS_H

#include "../util/globalshared.h"
#include "../util/serializable.h"

class DomFlags : public Serializable
{
public:
    DomFlags(eTimeType type);

};

#endif // FLAGS_H
