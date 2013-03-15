#include "model/identifieditem.h"

/**
 * 构造函数。
 */
IdentifiedItem::IdentifiedItem()
{
}

/**
 * 返回ID。
 * @return ID。
 */
int IdentifiedItem::id() const
{
    return this->_id;
}

/**
 * 设置ID。
 * @param id ID。
 */
void IdentifiedItem::setId(const int id)
{
    this->_id = id;
}
