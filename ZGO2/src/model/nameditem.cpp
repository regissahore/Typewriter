#include "model/nameditem.h"

/**
 * 构造函数。
 */
NamedItem::NamedItem()
{
}

/**
 * 获得名称。
 * @return 名称。
 */
const QString NamedItem::name() const
{
    return this->_name;
}

/**
 * 设置名称。
 * @param 名称。
 */
void NamedItem::setName(const QString name)
{
    this->_name = name;
}
