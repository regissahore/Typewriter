#include "typeditem.h"

TypedItem::TypedItem()
{
}

/**
 * 返回当前操作符的类型。
 * @return 操作符类型。
 */
int TypedItem::type() const
{
    return this->_type;
}

/**
 * 设置当前操作符的类型。
 * @param type 操作符类型。
 */
void TypedItem::setType(const int type)
{
    this->_type = type;
}
