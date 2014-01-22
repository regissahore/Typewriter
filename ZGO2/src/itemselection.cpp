#include "itemselection.h"

ItemSelection::ItemSelection(QGraphicsItem *parent) : ItemMoveable(parent)
{
}

const QPoint ItemSelection::end() const
{
    return this->_end;
}

int ItemSelection::left() const
{
    if (this->end().x() < 0)
    {
        return this->pos().x() + this->end().x();
    }
    return this->pos().x();
}

int ItemSelection::right() const
{
    if (this->end().x() < 0)
    {
        return this->pos().x();
    }
    return this->pos().x() + this->end().x();
}

int ItemSelection::top() const
{
    if (this->end().y() < 0)
    {
        return this->pos().y() + this->end().y();
    }
    return this->pos().y();
}

int ItemSelection::bottom() const
{
    if (this->end().y() < 0)
    {
        return this->pos().y();
    }
    return this->pos().y() + this->end().y();
}

bool ItemSelection::isInside(int x, int y) const
{
    return x > left() && x < right() && y > top() && y < bottom();
}

void ItemSelection::setEnd(const QPoint &end)
{
    this->_end.setX(end.x());
    this->_end.setY(end.y());
    this->prepareGeometryChange();
}

QRectF ItemSelection::boundingRect() const
{
    return QRectF(0, 0, this->end().x(), this->end().y());
}

void ItemSelection::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item);
    Q_UNUSED(widget);
    painter->setPen(Qt::darkGray);
    painter->setPen(Qt::DashLine);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(0, 0, this->end().x(), this->end().y());
}
