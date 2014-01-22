#include "typeditem.h"

TypedItem::TypedItem()
{
}

int TypedItem::type() const
{
    return this->_type;
}

void TypedItem::setType(const int type)
{
    this->_type = type;
}
