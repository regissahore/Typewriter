#include "view/itemgosource.h"

ItemGOSource::ItemGOSource()
{
}

int ItemGOSource::type() const
{
    return this->_type;
}

void ItemGOSource::setType(int type)
{
    this->_type = type;
}
