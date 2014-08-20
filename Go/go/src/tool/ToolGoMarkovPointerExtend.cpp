#include "ToolGoMarkovPointerExtend.h"
#include "ItemDrawable.h"
#include "DefinationEditorSelectionType.h"
#include "MessageFactory.h"
#include "SceneGo.h"
#include "GoOperator.h"
#include "ItemMoveable.h"
#include "ItemGoMarkovOperator.h"
#include "ItemGoMarkovEquivalent.h"
#include "ItemGoFactory.h"
#include "ItemGoText.h"
#include "GoMarkovOperator.h"
#include "ItemGoSignal.h"
#include "GoSignal.h"
#include "ViewGo.h"
#include "EditorGo.h"

ToolGoMarkovPointerExtend::ToolGoMarkovPointerExtend(SceneGo *sceneGo) : ToolGoPointerExtend(sceneGo)
{
}

bool ToolGoMarkovPointerExtend::mousePressStatusNullItem(QGraphicsSceneMouseEvent *event)
{
    if (this->_item != nullptr)
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
            this->sceneGo()->send(message);
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
                this->sceneGo()->send(message);
                return true;
            }
        }
    }
    return false;
}

void ToolGoMarkovPointerExtend::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_C)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            if (this->_item != nullptr)
            {
                if (this->_item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
                {
                    ItemGoMarkovOperator *item = ((ItemGoMarkovOperator*)this->_item)->copy();
                    this->sceneGo()->addItem(item);
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
                            ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
                            if (op->model()->id() < visit.size())
                            {
                                visit[op->model()->id()] = true;
                            }
                        }
                        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT || item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
                        {
                            ItemGoMarkovEquivalent *eq = (ItemGoMarkovEquivalent*)item;
                            if (eq->id() < visit.size())
                            {
                                visit[eq->id()] = true;
                            }
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
                            ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
                            if (op->model()->realID() < visit.size())
                            {
                                visit[op->model()->realID()] = true;
                            }
                        }
                        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT || item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
                        {
                            ItemGoMarkovEquivalent *eq = (ItemGoMarkovEquivalent*)item;
                            if (eq->id() < visit.size())
                            {
                                visit[eq->id()] = true;
                            }
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
                    this->sceneGo()->send(message);
                }
                else if (this->_item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_TEXT)
                {
                    ItemGoText *item = ((ItemGoText*)this->_item)->copy();
                    item->setX(((ItemGoText*)this->_item)->x() + 100);
                    item->setY(((ItemGoText*)this->_item)->y() + 100);
                    this->sceneGo()->addItem(item);
                    this->_item->setColor(Qt::black);
                    this->_item = item;
                    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
                    message->setMessage(this->_item);
                    this->sceneGo()->send(message);
                }
            }
            this->sceneGo()->viewGo()->editor()->setModified(true);
        }
    }
    else if (event->key() == Qt::Key_G)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            if (this->_item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
            {
                ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)this->_item;
                if (event->modifiers() & Qt::ShiftModifier)
                {
                    ((GoMarkovOperator*)op->model())->setIsGlobalFeedback(false);
                }
                else
                {
                    ((GoMarkovOperator*)op->model())->setIsGlobalFeedback(true);
                }
                op->update();
            }
            else if (this->_item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
            {
                ItemGoSignal *signal = (ItemGoSignal*)this->_item;
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
            this->sceneGo()->viewGo()->editor()->setModified(true);
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
            message->setMessage(this->_item);
            this->sceneGo()->send(message);
        }
    }
    else if (event->key() == Qt::Key_P)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            if (this->_item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
            {
                ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
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
            this->sceneGo()->viewGo()->editor()->setModified(true);
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
            message->setMessage(this->_item);
            this->sceneGo()->send(message);
        }
    }
    else if (event->key() == Qt::Key_Delete)
    {
        if (this->_item != nullptr)
        {
            ItemGoFactory::deleteItem(this->_item);
            this->_item = nullptr;
            this->sceneGo()->viewGo()->editor()->setModified(true);
        }
    }
}
