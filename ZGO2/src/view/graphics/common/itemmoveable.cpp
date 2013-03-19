#include "itemmoveable.h"

/**
 * 构造函数。
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
 * 鼠标按下事件。
 * @param event 鼠标事件。
 */
void ItemMoveable::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->_mousePressPosition = event->scenePos();
    update();
}

/**
 * 鼠标移动事件。
 * @param event 鼠标事件。
 */
void ItemMoveable::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(this->pos() + event->scenePos() - this->_mousePressPosition);
    this->_mousePressPosition = event->scenePos();
    this->update();
}

/**
 * 鼠标抬起事件。
 * @param event 鼠标事件。
 */
void ItemMoveable::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    update();
}
