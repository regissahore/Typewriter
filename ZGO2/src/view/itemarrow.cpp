#include "view/itemarrow.h"

/**
 * 构造函数。
 */
ItemArrow::ItemArrow(QGraphicsItem *parent) : ItemDrawable(parent)
{
    this->setSize(0, 0);
}

/**
 * 获得终止位置。
 * @return 终止位置。
 */
const QPoint ItemArrow::end() const
{
    return this->_end;
}

/**
 * 设置终止位置。
 * @param start 终止位置。
 */
void ItemArrow::setEnd(const QPoint &end)
{
    this->_end.setX(end.x());
    this->_end.setY(end.y());
}

/**
 * 绘制箭头。
 * @param painter 画笔。
 * @param item 配置信息。
 * @param widget 绘制窗体。
 */
void ItemArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawLine(QPoint(0, 0), this->end());
    double angle = atan2(this->end().y(), this->end().x());
    angle = angle + PI;
    double angle1 = angle + PI * 0.08;
    double angle2 = angle - PI * 0.08;
    QPointF points[3];
    points[0].setX(this->end().x());
    points[0].setY(this->end().y());
    points[1].setX(this->end().x() + 15.0 * cos(angle1));
    points[1].setY(this->end().y() + 15.0 * sin(angle1));
    points[2].setX(this->end().x() + 15.0 * cos(angle2));
    points[2].setY(this->end().y() + 15.0 * sin(angle2));
    painter->drawPolygon(points, 3);
}
