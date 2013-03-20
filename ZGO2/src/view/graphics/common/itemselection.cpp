#include "itemselection.h"

/**
 * Constructor.
 * @param parent The parent item.
 */
ItemSelection::ItemSelection(QGraphicsItem *parent) : ItemMoveable(parent)
{
    this->setSize(0, 0);
}

/**
 * Get the end position.
 * @return End position.
 */
const QPoint ItemSelection::end() const
{
    return this->_end;
}

/**
 * Get the left border of the selection.
 * @return Left border.
 */
int ItemSelection::left() const
{
    if (this->end().x() < 0)
    {
        return this->pos().x() + this->end().x();
    }
    return this->pos().x();
}

/**
 * Get the right border of the selection.
 * @return Right border.
 */
int ItemSelection::right() const
{
    if (this->end().x() < 0)
    {
        return this->pos().x();
    }
    return this->pos().x() + this->end().x();
}

/**
 * Get the top border of the selection.
 * @return Top border.
 */
int ItemSelection::top() const
{
    if (this->end().y() < 0)
    {
        return this->pos().y() + this->end().y();
    }
    return this->pos().y();
}

/**
 * Get the bottom border of the selection.
 * @return Bottom border.
 */
int ItemSelection::bottom() const
{
    if (this->end().y() < 0)
    {
        return this->pos().y();
    }
    return this->pos().y() + this->end().y();
}

/**
 * Whether the position is inside the selection.
 * @return Returns true if the position is inside, otherwise false.
 */
bool ItemSelection::isInside(int x, int y) const
{
    return x > left() && x < right() && y > top() && y < bottom();
}

/**
 * Set the end position.
 * @param end End position.
 */
void ItemSelection::setEnd(const QPoint &end)
{
    this->_end.setX(end.x());
    this->_end.setY(end.y());
}

/**
 * Draw rectangle.
 * @param painter Painter.
 * @param item Option.
 * @param widget Widget.
 */
void ItemSelection::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item);
    Q_UNUSED(widget);
    painter->setPen(Qt::DashLine);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(0, 0, this->end().x(), this->end().y());
}
