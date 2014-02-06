#include "ToolGoPointer.h"
#include "SceneGo.h"
#include "DefinationEditorSelectionType.h"
#include "ItemGoSignal.h"
#include "MessageFactory.h"
#include "ItemGoFactory.h"

ToolGoPointer::ToolGoPointer(SceneGo *sceneGo) : ToolGoAbstract(sceneGo)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->_item = nullptr;
    this->setMoving(false);
}

void ToolGoPointer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->_item = nullptr;
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
            ItemGoFactory::sendSelectionMessage(this->sceneGo(), (ItemDrawable*)items[i]);
            this->_item = (ItemDrawable*)items[i];
            break;
        }
    }
}


void ToolGoPointer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_moving)
    {
        ((ItemMoveable*)this->_item)->move(event);
    }
}

void ToolGoPointer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_moving)
    {
        ((ItemMoveable*)this->_item)->stopMove(event);
        setMoving(false);
        ItemGoFactory::sendSelectionMessage(this->sceneGo(), this->_item);
    }
}

void ToolGoPointer::setMoving(bool value)
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

void ToolGoPointer::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        if (this->_item != nullptr)
        {
            ItemGoFactory::deleteItem(this->_item);
            this->_item = nullptr;
        }
    }
}
