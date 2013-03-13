#include "VAGoMoveable.h"

/**
 * 构造函数。
 */
VAGoMoveable::VAGoMoveable()
{
}

/**
 * 当前是否移动。
 * @return bool 如果正在移动返回true，否则返回false。
 */
bool VAGoMoveable::isMoving(void) const
{
    return this->_moving;
}

/**
 * 设置是否移动。
 * @return bool 目标值。
 */
void VAGoMoveable::setMoving(bool value)
{
    this->_moving = value;
}
