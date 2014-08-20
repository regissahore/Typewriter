#include "ItemArrow.h"

ItemArrow::ItemArrow(QGraphicsItem *parent) : ItemDrawable(parent)
{
    this->setIsShowArrow(true);
}

const QPoint ItemArrow::end() const
{
    return this->_end;
}

void ItemArrow::setEnd(const QPoint &end)
{
    this->_end.setX(end.x());
    this->_end.setY(end.y());
}

void ItemArrow::setEnd(const int x, const int y)
{
    this->_end.setX(x);
    this->_end.setY(y);
    this->update();
    this->prepareGeometryChange();
}

QPoint ItemArrow::sceneEnd()
{
    return QPoint(this->pos().x() + this->end().x(),
                  this->pos().y() + this->end().y());
}

bool ItemArrow::isShowArrow() const
{
    return this->_isShowArrow;
}

void ItemArrow::setIsShowArrow(const bool value)
{
    this->_isShowArrow = value;
}

QRectF ItemArrow::boundingRect() const
{
    return QRectF(0, 0, this->end().x(), this->end().y());
}

void ItemArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item);
    Q_UNUSED(widget);
    painter->setPen(Qt::SolidLine);
    painter->setPen(this->_color);
    painter->setBrush(this->_color);
    painter->drawLine(QPoint(0, 0), this->end());
    if (isShowArrow())
    {
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
}
