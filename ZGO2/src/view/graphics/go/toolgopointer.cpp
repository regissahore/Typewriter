#include "toolgopointer.h"

/**
 * Set the graphics drag mode to pointer.
 * @param sceneGO The SceneGO entity.
 */
ToolGOPointer::ToolGOPointer(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->_item = 0L;
    this->setMoving(false);
}

void ToolGOPointer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_moving)
    {
        this->_item->mouseMoveEvent(event);
    }
}

void ToolGOPointer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    ItemDrawable* drawable = (ItemDrawable*)this->graphicsScene()->itemAt(event->scenePos().x(), event->scenePos().y());
    if (0L == drawable)
    {
        setMoving(false);
    }
    else if (!drawable->moveable())
    {
        setMoving(false);
    }
    else
    {
        this->_item = (ItemMoveable*)drawable;
        setMoving(true);
        MessageFactoryTool *factory = new MessageFactoryTool();
        Message* message = new Message();
        message->setMessage(this->_item);
        this->sceneGO()->sendMessage(message);
        delete factory;
        this->_item->mousePressEvent(event);
    }
}

void ToolGOPointer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_moving)
    {
        this->_item->mouseReleaseEvent(event);
        setMoving(false);
    }
}

void ToolGOPointer::setMoving(bool value)
{
    this->_moving = value;
    if (value)
    {
        this->graphicsView()->setCursor(Qt::SizeAllCursor);
    }
    else
    {
        this->graphicsView()->setCursor(Qt::ArrowCursor);
    }
}
