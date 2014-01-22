#include "IdentifiedItem.h"

IdentifiedItem::IdentifiedItem()
{
    this->setId(0);
}

int IdentifiedItem::id() const
{
    return this->_id;
}

void IdentifiedItem::setId(const int id)
{
    this->_id = id;
}
