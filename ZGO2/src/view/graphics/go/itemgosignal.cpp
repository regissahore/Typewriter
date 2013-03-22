#include "itemgosignal.h"
#include "itemgooperator.h"
#include "definationgotype.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOSignal::ItemGOSignal(QGraphicsItem *parent) : ItemDrawable(parent)
{
    this->_start = new SignalConnection();
    this->_end = new SignalConnection();
    this->_start->op = 0L;
    this->_end->op = 0L;
}

/**
 * Destructor.
 */
ItemGOSignal::~ItemGOSignal()
{
    this->setParentItem(0L);
    delete this->_start;
    delete this->_end;
}

/**
 * Return the shape of the object.
 * @return Shape.
 */
QPainterPath ItemGOSignal::shape() const
{
    QPainterPath path;
    path.addRect(-2, -2,
                 (this->_endPos.x() >> 1) + 4, 4);
    path.addRect((this->_endPos.x() >> 1) - 2, -2,
                 4, this->_endPos.y() + 4);
    path.addRect((this->_endPos.x() >> 1) - 2, this->_endPos.y() - 2,
                 (this->_endPos.x() >> 1) + 4, 4);
    return path;
}

/**
 * Get the start structure.
 * @return Start structure.
 */
ItemGOSignal::SignalConnection* ItemGOSignal::start()
{
    return this->_start;
}

/**
 * Get the end structure.
 * @return End structure.
 */
ItemGOSignal::SignalConnection* ItemGOSignal::end()
{
    return this->_end;
}

/**
 * Set the end position.
 * @param x X position.
 * @param y Y position.
 */
void ItemGOSignal::setEndPosition(int x, int y)
{
    this->_endPos.setX(x);
    this->_endPos.setY(y);
    this->update();
}

/**
 * Set the end position.
 * @param pos End position.
 */
void ItemGOSignal::setEndPosition(QPointF pos)
{
    this->_endPos.setX(pos.x());
    this->_endPos.setY(pos.y());
    this->update();
}

/**
 * Paint a line.
 * @param painter The painter.
 * @param item The option.
 * @param widget The widget.
 */
void ItemGOSignal::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item);
    Q_UNUSED(widget);
    painter->drawLine(QPointF(0, 0), QPointF(this->_endPos.x() >> 1, 0));
    painter->drawLine(QPointF(this->_endPos.x() >> 1, 0), QPointF(this->_endPos.x() >> 1, this->_endPos.y()));
    painter->drawLine(QPointF(this->_endPos.x() >> 1, this->_endPos.y()), this->_endPos);
}

/**
 * Update the position.
 */
void ItemGOSignal::updatePosition()
{
    if (this->start()->op != 0L && this->end()->op != 0L)
    {
        switch (this->start()->type)
        {
        case DefinationGOType::GO_OPERATOR_INPUT:
            this->setPos(this->start()->op->pos() + this->start()->op->getInputPosition(this->start()->index));
            break;
        case DefinationGOType::GO_OPERATOR_SUBINPUT:
            this->setPos(this->start()->op->pos() + this->start()->op->getSubInputPosition(this->start()->index));
            break;
        case DefinationGOType::GO_OPERATOR_OUTPUT:
            this->setPos(this->start()->op->pos() + this->start()->op->getOutputPosition(this->start()->index));
            break;
        }
        switch (this->end()->type)
        {
        case DefinationGOType::GO_OPERATOR_INPUT:
            this->setEndPosition(this->end()->op->pos() + this->end()->op->getInputPosition(this->end()->index) - this->pos());
            break;
        case DefinationGOType::GO_OPERATOR_SUBINPUT:
            this->setEndPosition(this->end()->op->pos() + this->end()->op->getSubInputPosition(this->end()->index) - this->pos());
            break;
        case DefinationGOType::GO_OPERATOR_OUTPUT:
            this->setEndPosition(this->end()->op->pos() + this->end()->op->getOutputPosition(this->end()->index) - this->pos());
            break;
        }
        this->update();
    }
}

/**
 * Remove the connection of the signal.
 */
void ItemGOSignal::removeConnection()
{
    if (this->_start->op != 0L)
    {
        this->start()->op->removeSignal(this, this->start()->type, this->start()->index);
    }
    if (this->_end->op != 0L)
    {
        this->end()->op->removeSignal(this, this->end()->type, this->end()->index);
    }
}
