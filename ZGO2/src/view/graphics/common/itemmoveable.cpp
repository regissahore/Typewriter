#include "itemmoveable.h"

/**
 * Constructor.
 * @param parent Parent graphics item.
 */
ItemMoveable::ItemMoveable(QGraphicsItem *parent) : ItemDrawable(parent)
{
}

/**
 * Whether the item is moveable.
 * @return Returns true if the item is moveable, otherwise false.
 */
bool ItemMoveable::moveable() const
{
    return true;
}

/**
 * Start moving the item.
 * @param event Mouse event.
 */
void ItemMoveable::startMove(QGraphicsSceneMouseEvent *event)
{
    this->_mousePressPosition = event->scenePos();
    update();
}

/**
 * Moving the item.
 * @param event Mouse event.
 */
void ItemMoveable::move(QGraphicsSceneMouseEvent *event)
{
    this->setPos(this->pos() + event->scenePos() - this->_mousePressPosition);
    this->_mousePressPosition = event->scenePos();
    this->update();
}

/**
 * Stop moving the item.
 * @param event Mouse event.
 */
void ItemMoveable::stopMove(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    update();
}
