#include "nameditem.h"

NamedItem::NamedItem()
{
}

const QString NamedItem::name() const
{
    return this->_name;
}

void NamedItem::setName(const QString name)
{
    this->_name = name;
}
