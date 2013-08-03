#include "toolgomarkovpointerextend.h"
#include "itemdrawable.h"
#include "definationeditorselectiontype.h"
#include "messagefactory.h"
#include "scenego.h"
#include "gooperator.h"
#include "itemmoveable.h"
#include "itemgomarkovoperator.h"
#include "itemgomarkovequivalent.h"
#include "itemgofactory.h"

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
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT ||
                item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
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
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT ||
                item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
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
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT ||
                item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
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

void ToolGOMarkovPointerExtend::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_C)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            if (this->_item != 0L)
            {
                if (this->_item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
                {
                    ItemGOMarkovOperator *item = ((ItemGOMarkovOperator*)this->_item)->copy();
                    this->sceneGO()->addItem(item);
                    this->_item->setColor(Qt::black);
                    QList<QGraphicsItem*> items = this->graphicsScene()->items();
                    QVector<bool> visit;
                    for (int i = 0; i <= items.size() + 1; ++i)
                    {
                        visit.push_back(false);
                    }
                    for (int i = 0; i < items.size(); ++i)
                    {
                        ItemDrawable* item = (ItemDrawable*)items.at(i);
                        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
                        {
                            ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)item;
                            visit[op->model()->id()] = true;
                        }
                        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
                        {
                            ItemGOMarkovEquivalent *eq = (ItemGOMarkovEquivalent*)item;
                            visit[eq->id()] = true;
                        }
                    }
                    for (int i = 1; i <= items.size() + 1; ++i)
                    {
                        if (!visit[i])
                        {
                            item->model()->setId(i);
                            break;
                        }
                    }
                    this->_item = item;
                    this->_item->setColor(QColor(Qt::darkBlue));
                    Message *message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
                    message->setMessage(this->_item);
                    this->sceneGO()->sendMessage(message);
                }
            }
        }
    }
    else if (event->key() == Qt::Key_Delete)
    {
        if (this->_item != 0L)
        {
            ItemGOFactory::deleteItem(this->_item);
            this->_item = 0L;
        }
    }
}
