#include "location.h"

Location::Location()
{
    this->mType = UNDEFINED;
}

QString Location::getName()
{
    return this->mName;
}

eLocationType Location::getType()
{
    return this->mType;
}
