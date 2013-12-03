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
#include "itemgotext.h"
#include "gomarkovoperator.h"
#include "itemgosignal.h"
#include "gosignal.h"
#include "viewgo.h"
#include "editorgo.h"

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
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
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
                QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
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
                        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT || item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
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

                    visit.clear();
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
                            visit[op->model()->realID()] = true;
                        }
                        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT || item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
                        {
                            ItemGOMarkovEquivalent *eq = (ItemGOMarkovEquivalent*)item;
                            visit[eq->id()] = true;
                        }
                    }
                    for (int i = 1; i <= items.size() + 1; ++i)
                    {
                        if (!visit[i])
                        {
                            item->model()->setRealID(i);
                            break;
                        }
                    }

                    this->_item = item;
                    this->_item->setColor(QColor(Qt::darkBlue));
                    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
                    message->setMessage(this->_item);
                    this->sceneGO()->sendMessage(message);
                }
                else if (this->_item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_TEXT)
                {
                    ItemGOText *item = ((ItemGOText*)this->_item)->copy();
                    item->setX(((ItemGOText*)this->_item)->x() + 100);
                    item->setY(((ItemGOText*)this->_item)->y() + 100);
                    this->sceneGO()->addItem(item);
                    this->_item->setColor(Qt::black);
                    this->_item = item;
                    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
                    message->setMessage(this->_item);
                    this->sceneGO()->sendMessage(message);
                }
            }
            this->sceneGO()->viewGO()->editor()->setModified(true);
        }
    }
    else if (event->key() == Qt::Key_G)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            if (this->_item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
            {
                ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)this->_item;
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    ((GOMarkovOperator*)op->model())->setIsGlobalFeedback(false);
                }
                else
                {
                    ((GOMarkovOperator*)op->model())->setIsGlobalFeedback(true);
                }
                op->update();
            }
            else if (this->_item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
            {
                ItemGOSignal *signal = (ItemGOSignal*)this->_item;
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    signal->model()->setIsGlobalFeedback(false);
                }
                else
                {
                    signal->model()->setIsGlobalFeedback(true);
                }
                signal->update();
            }
            this->sceneGO()->viewGO()->editor()->setModified(true);
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
            message->setMessage(this->_item);
            this->sceneGO()->sendMessage(message);
        }
    }
    else if (event->key() == Qt::Key_P)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            if (this->_item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
            {
                ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    item->setIsDrawParameter(false);
                }
                else
                {
                    item->setIsDrawParameter(true);
                }
                item->update();
            }
            this->sceneGO()->viewGO()->editor()->setModified(true);
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
            message->setMessage(this->_item);
            this->sceneGO()->sendMessage(message);
        }
    }
    else if (event->key() == Qt::Key_Delete)
    {
        if (this->_item != 0L)
        {
            ItemGOFactory::deleteItem(this->_item);
            this->_item = 0L;
            this->sceneGO()->viewGO()->editor()->setModified(true);
        }
    }
}
