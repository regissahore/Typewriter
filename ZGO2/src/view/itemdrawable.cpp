#include "view/itemdrawable.h"

/**
 * 构造函数。
 */
ItemDrawable::ItemDrawable(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->setSize(40, 40);
}

/**
 * 返回矩形边界。
 * @return 边界。
 */
QRectF ItemDrawable::boundingRect() const
{
    return QRectF(0, 0, this->width(), this->height());
}

/**
 * 绘制函数。
 * @param painter 画笔。
 * @param item 配置信息。
 * @param widget 绘制窗体。
 */
void ItemDrawable::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::darkGray);
    painter->drawRect(0, 0, this->width(), this->height());
}

/**
 * 返回当前的大小。
 * @return 大小。
 */
QSize ItemDrawable::size() const
{
    return QSize(this->width(), this->height());
}

/**
 * 返回宽度。
 * @return 宽度。
 */
qreal ItemDrawable::width() const
{
    return this->_width;
}

/**
 * 返回高度。
 * @return 高度。
 */
qreal ItemDrawable::height() const
{
    return this->_height;
}

/**
 * 设置宽度。
 * @param width 宽度。
 */
void ItemDrawable::setWidth(qreal width)
{
    this->_width = width;
}

/**
 * 设置高度。
 * @param height 高度。
 */
void ItemDrawable::setHeight(qreal height)
{
    this->_height = height;
}

/**
 * 设置大小。
 * @param width 宽度。
 * @param height 高度。
 */
void ItemDrawable::setSize(qreal width, qreal height)
{
    this->setWidth(width);
    this->setHeight(height);
}
