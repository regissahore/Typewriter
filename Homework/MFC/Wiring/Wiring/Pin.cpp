#include "stdafx.h"
#include "Pin.h"

/**
 * 构造函数。默认引脚在左上角。
 */
Pin::Pin()
{
    this->setOrientation(ORI_TOP);
    this->setShift(0.0);
}


Pin::~Pin()
{
}

/**
 * 设置引脚的方位。
 * @param orientation 引脚的方位。
 */
void Pin::setOrientation(const Orientation orientation)
{
    this->_orientation = orientation;
}

/**
 * 返回引脚的方位。
 * @return orientation 引脚的方位。
 */
Pin::Orientation Pin::orientation() const
{
    return this->_orientation;
}

/**
 * 设置引脚的偏移量。
 * 如果引脚在上下方位，则偏移量为横向距芯片左端的距离。
 * 如果引脚在左右方位，则偏移量为纵向距芯片上端的距离。
 * @param shift 偏移量。
 */
void Pin::setShift(const double shift)
{
    this->_shift = shift;
}

/**
 * 返回引脚的偏移量。
 * @see setShift
 * @return 偏移量。
 */
double Pin::shift() const
{
    return this->_shift;
}

/**
 * 设置引脚的编号。
 * @param id 编号。
 */
void Pin::setId(const int id)
{
    this->_id = id;
}

/**
 * 获取引脚的编号。
 * @return 编号。
 */
int Pin::id() const
{
    return this->_id;
}

/**
 * 按圆周对引脚进行排序。
 * @param a 引脚1。
 * @param b 引脚2。
 * @return 如果排名靠前返回true。
 */
bool operator <(const Pin &a, const Pin &b)
{
    if (a.orientation() == b.orientation())
    {
        if (a.orientation() == Pin::ORI_TOP || a.orientation() == Pin::ORI_RIGHT)
        {
            return a.shift() < b.shift();
        }
        else
        {
            return a.shift() > b.shift();
        }
    }
    return a.orientation() < b.orientation();
}