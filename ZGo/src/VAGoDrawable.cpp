#include "VAGoDrawable.h"

/**
 * 构造函数。
 */
VAGoDrawable::VAGoDrawable()
{
}

/**
 * 矩形范围。
 * @return 范围。
 */
QRectF VAGoDrawable::boundingRect() const
{
    return QRectF(this->x(), this->y(), this->width(), this->height());
}

/**
 * 返回当前图形长度。
 * @return 长度。
 */
qreal VAGoDrawable::width(void) const
{
    return this->_width;
}

/**
 * 返回当前图形宽度。
 * @return 宽度。
 */
qreal VAGoDrawable::height(void) const
{
    return this->_height;
}

/**
 * 返回当前图形的大小。
 * @return 大小。
 */
QSize VAGoDrawable::size(void) const
{
    return QSize(this->width(), this->height());
}

/**
 * 设置当前图形长度。
 * @param width 长度。
 */
void VAGoDrawable::setWidth(qreal width)
{
    this->_width = width;
    this->update();
}

/**
 * 设置当前图形宽度。
 * @param height 宽度。
 */
void VAGoDrawable::setHeight(qreal height)
{
    this->_height = height;
    this->update();
}

/**
 * 设置当前图形的大小。
 * @param width 长度。
 * @param height 宽度。
 */
void VAGoDrawable::setSize(qreal width, qreal height)
{
    this->setWidth(width);
    this->setHeight(height);
}

/**
 * 设置当前图形的大小。
 * @param size 大小。
 */
void VAGoDrawable::setSize(QSize size)
{
    this->setWidth(size.width());
    this->setHeight(size.height());
}

/**
 * 当前是否获得焦点。
 * @return bool 如果获得了焦点返回true，否则返回false。
 */
bool VAGoDrawable::isFocus(void) const
{
    return this->_focus;
}

/**
 * 设置是否获得焦点。
 * @param value 要设置的值。
 */
void VAGoDrawable::setFocus(bool value)
{
    this->_focus = value;
}
