#include "MAGoItem.h"

/**
 * 获取唯一的ID。
 * @return ID。
 */
qint32 MAGoItem::id(void) const
{
    return this->_id;
}

/**
 * 设置唯一的ID。
 * @param id ID。
 */
void MAGoItem::setId(qint32 id)
{
    this->_id = id;
}

/**
 * 获取类型。
 * @return 类型。
 */
qint32 MAGoItem::type(void) const
{
    return this->_type;
}

/**
 * 设置类型。
 * @return param 类型。
 */
void MAGoItem::setType(qint32 type)
{
    this->_type = type;
}
