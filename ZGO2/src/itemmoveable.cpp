#include "itemmoveable.h"

ItemMoveable::ItemMoveable(QGraphicsItem *parent) : ItemDrawable(parent)
{
}

bool ItemMoveable::moveable() const
{
    return true;
}

void ItemMoveable::startMove(QGraphicsSceneMouseEvent *event)
{
    this->_mousePressPosition = event->scenePos();
    update();
}

void ItemMoveable::move(QGraphicsSceneMouseEvent *event)
{
    this->setPos(this->pos() + event->scenePos() - this->_mousePressPosition);
    this->_mousePressPosition = event->scenePos();
    this->update();
}

void ItemMoveable::stopMove(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    update();
}
