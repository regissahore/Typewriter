#include "toolgopointer.h"
#include "scenego.h"
#include "definationeditorselectiontype.h"
#include "itemgosignal.h"
#include "messagefactory.h"
#include "itemgofactory.h"

ToolGOPointer::ToolGOPointer(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->_item = 0L;
    this->setMoving(false);
}

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
            if (item->isSelectable(event->scenePos().x(), event->scenePos().y()))
            {
                this->_item = (ItemDrawable*)item;
                setMoving(true);
                ((ItemMoveable*)this->_item)->startMove(event);
                return;
            }
        }
    }
    for (int i = 0; i < items.size(); ++i)
    {
        if (((ItemDrawable*)items[i])->isSelectable(event->scenePos().x(), event->scenePos().y()))
        {
            ItemGOFactory::sendSelectionMessage(this->sceneGO(), (ItemDrawable*)items[i]);
            this->_item = (ItemDrawable*)items[i];
            break;
        }
    }
}


void ToolGOPointer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_moving)
    {
        ((ItemMoveable*)this->_item)->move(event);
    }
}

void ToolGOPointer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_moving)
    {
        ((ItemMoveable*)this->_item)->stopMove(event);
        setMoving(false);
        ItemGOFactory::sendSelectionMessage(this->sceneGO(), this->_item);
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
