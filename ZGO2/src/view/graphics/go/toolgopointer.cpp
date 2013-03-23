#include "toolgopointer.h"
#include "scenego.h"
#include "definationeditorselectiontype.h"
#include "itemgosignal.h"
#include "messagefactoryeditor.h"
#include "itemgofactory.h"

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

/**
 * Select a item if there exist one.
 * @param Mouse event.
 */
void ToolGOPointer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->_item = 0L;
    QList<QGraphicsItem*> items = this->graphicsScene()->items(event->scenePos());
    setMoving(false);
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable* item = (ItemDrawable*)items[i];
        if (item->moveable())
        {
            if (item->isSelected(event->scenePos().x(), event->scenePos().y()))
            {
                this->_item = (ItemDrawable*)item;
                setMoving(true);
                ItemGOFactory::sendSelectionMessage(this->sceneGO(), this->_item);
                ((ItemMoveable*)this->_item)->startMove(event);
                return;
            }
        }
    }
    for (int i = 0; i < items.size(); ++i)
    {
        if (((ItemDrawable*)items[i])->isSelected(event->scenePos().x(), event->scenePos().y()))
        {
            ItemGOFactory::sendSelectionMessage(this->sceneGO(), (ItemDrawable*)items[i]);
            this->_item = (ItemDrawable*)items[i];
            break;
        }
    }
}


/**
 * Move the item if one item is selected.
 * @param Mouse event.
 */
void ToolGOPointer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_moving)
    {
        ((ItemMoveable*)this->_item)->move(event);
    }
}

/**
 * Stop moving if it is moving.
 * @param event Mouse event.
 */
void ToolGOPointer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_moving)
    {
        ((ItemMoveable*)this->_item)->stopMove(event);
        setMoving(false);
    }
}

/**
 * Set if the item is moving, it will set the cursor at the same time.
 * @param value The boolean value.
 */
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

/**
 * Key release event.
 * @param event Key event.
 */
void ToolGOPointer::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        if (this->_item != 0L)
        {
            ItemGOFactory::deleteItem(this->_item);
            this->_item = 0L;
        }
    }
}
