#include "toolgomarkovpointerextend.h"
#include "itemdrawable.h"
#include "definationeditorselectiontype.h"
#include "messagefactory.h"
#include "scenego.h"
#include "itemmoveable.h"

ToolGOMarkovPointerExtend::ToolGOMarkovPointerExtend(SceneGO *sceneGO) : ToolGOPointerExtend(sceneGO)
{
}

bool ToolGOMarkovPointerExtend::mousePressStatusNullItem(QGraphicsSceneMouseEvent *event)
{
    if (this->_item != 0L)
    {
        this->_item->setColor(Qt::black);
    }
    QList<QGraphicsItem*> items = this->graphicsScene()->items(event->scenePos());
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable* item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            continue;
        }
        if (item->moveable())
        {
            if (item->isSelectable(event->scenePos().x(), event->scenePos().y()))
            {
                this->_item = (ItemDrawable*)item;
                this->_status = Status_Item_Moving;
                this->graphicsView()->setCursor(Qt::SizeAllCursor);
                ((ItemMoveable*)this->_item)->startMove(event);
                return true;
            }
        }
    }
    for (int i = 0 ; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            continue;
        }
        if (item->isSelectable(event->scenePos().x(), event->scenePos().y()))
        {
            this->_item = (ItemDrawable*)item;
            this->_item->setColor(QColor(Qt::darkBlue));
            Message *message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
            message->setMessage(this->_item);
            this->sceneGO()->sendMessage(message);
            return true;
        }
    }
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable* item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            if (item->isSelectable(event->scenePos().x(), event->scenePos().y()))
            {
                this->_item = (ItemDrawable*)item;
                this->_item->setColor(QColor(Qt::darkBlue));
                Message *message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
                message->setMessage(this->_item);
                this->sceneGO()->sendMessage(message);
                return true;
            }
        }
    }
    return false;
}
