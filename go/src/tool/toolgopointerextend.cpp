#include <QVector>
#include <qmath.h>
#include "SceneGo.h"
#include "ToolGoPointerExtend.h"
#include "DefinationGoType.h"
#include "DefinationEditorSelectionType.h"
#include "ItemDrawable.h"
#include "ItemMoveable.h"
#include "ItemGoOperator.h"
#include "ItemGoSignal.h"
#include "ItemGoFactory.h"
#include "GoOperator.h"
#include "GoSignal.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "MessageFactory.h"
#include "ViewGo.h"
#include "EditorGo.h"
#include "ItemGoMarkovOperator.h"

ToolGoPointerExtend::ToolGoPointerExtend(SceneGo *sceneGo) : ToolGoAbstract(sceneGo)
{
    this->_item = 0L;
    this->_signal = 0L;
    this->_status = Status_Null;
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->graphicsView()->setCursor(Qt::ArrowCursor);
}

ToolGoPointerExtend::~ToolGoPointerExtend()
{
    this->ToolGoAbstract::~ToolGoAbstract();
    if (this->_item != 0L)
    {
        this->_item->setColor(QColor(Qt::black));
    }
}

void ToolGoPointerExtend::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->_status)
    {
    case Status_Null:
        this->mousePressStatusNull(event);
        break;
    default:
        break;
    }
}

void ToolGoPointerExtend::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->_status)
    {
    case Status_Null:
        this->mouseMoveStatusNull(event);
        break;
    case Status_Signal_Connecting:
        this->mouseMoveStatusSignalConnecting(event);
        break;
    case Status_Item_Moving:
        this->mouseMoveStatusItemMoving(event);
        break;
    case Status_Signal_Adjusting:
        this->mouseMoveStatusSignalAdjusting(event);
        break;
    default:
        break;
    }
}

void ToolGoPointerExtend::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->_status)
    {
    case Status_Null:
        this->mouseReleaseStatusNull(event);
        break;
    case Status_Signal_Connecting:
        this->mouseReleaseStatusSignalConnecting(event);
        break;
    case Status_Item_Moving:
        this->mouseReleaseStatusItemMoving(event);
        break;
    case Status_Scene_Moving:
        this->mouseReleaseStatusSceneMoving(event);
        break;
    case Status_Signal_Adjusting:
        this->mouseReleaseStatusSignalAdjusting(event);
        break;
    default:
        break;
    }
}

void ToolGoPointerExtend::keyReleaseEvent(QKeyEvent *event)
{
    switch (this->_status)
    {
    case Status_Null:
        if (event->key() == Qt::Key_Delete)
        {
            if (this->_item != 0L)
            {
                ItemGoFactory::deleteItem(this->_item);
                this->_item = 0L;
            }
        }
        this->sceneGo()->viewGo()->editor()->setModified(true);
        break;
    default:
        break;
    }
}

bool ToolGoPointerExtend::isAround(QPointF pos1, QPointF pos2)
{
    return (pos1.x() - pos2.x()) * (pos1.x() - pos2.x()) +
            (pos1.y() - pos2.y()) * (pos1.y() - pos2.y()) <= 81;
}

void ToolGoPointerExtend::mousePressStatusNull(QGraphicsSceneMouseEvent *event)
{
    if (!this->mousePressStatusNullSignal(event))
    {
        if (!this->mousePressStatusNullSignalAdjust(event))
        {
            event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                                       ((int)event->scenePos().y() / 10) * 10));
            if (!this->mousePressStatusNullItem(event))
            {
                this->mousePressStatusNullScene(event);
            }
        }
    }
}

bool ToolGoPointerExtend::mousePressStatusNullSignal(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> items = this->graphicsScene()->items(QRectF(event->scenePos().x() - 100, event->scenePos().y() - 100, 200, 200));
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR || item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoOperator *op = (ItemGoOperator*)items.at(i);
            GoOperator *model = op->model();
            for (int j = 0; j < model->output()->number(); ++j)
            {
                if (this->isAround(event->scenePos(), op->pos() + op->getOutputPosition(j)))
                {
                    this->_status = Status_Signal_Connecting;
                    this->_signal = new ItemGoSignal();
                    items = this->graphicsScene()->items();
                    this->_signal->model()->setId(model->id());
                    this->_signal->start()->id = op->model()->realID();
                    this->_signal->start()->op = op;
                    this->_signal->start()->index = j;
                    this->_signal->start()->type = DefinationGoType::GO_OPERATOR_OUTPUT;
                    this->graphicsScene()->addItem(this->_signal);
                    this->_signal->setPos(op->pos() + op->getOutputPosition(j));
                    this->graphicsView()->setCursor(Qt::CrossCursor);
                    return true;
                }
            }
        }
    }
    return false;
}

bool ToolGoPointerExtend::mousePressStatusNullSignalAdjust(QGraphicsSceneMouseEvent *event)
{
    if (this->_item != 0L)
    {
        this->_item->setColor(QColor(Qt::black));
    }
    QList<QGraphicsItem*> items = this->graphicsScene()->items(QRectF(event->scenePos().x() - 100, event->scenePos().y() - 100, 200, 200));
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            ItemGoSignal *signal = (ItemGoSignal*)items.at(i);
            if (signal->isCornerLineSelectable(event->scenePos().x(), event->scenePos().y()))
            {
                this->_status = Status_Signal_Adjusting;
                this->_item = signal;
                this->_item->setColor(QColor(Qt::darkBlue));
                QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
                message->setMessage(this->_item);
                this->sceneGo()->sendMessage(message);
                this->graphicsView()->setCursor(Qt::SizeHorCursor);
                return true;
            }
        }
    }
    return false;
}

bool ToolGoPointerExtend::mousePressStatusNullItem(QGraphicsSceneMouseEvent *event)
{
    if (this->_item != 0L)
    {
        this->_item->setColor(Qt::black);
    }
    QList<QGraphicsItem*> items = this->graphicsScene()->items(event->scenePos());
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable* item = (ItemDrawable*)items[i];
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
        if (item->isSelectable(event->scenePos().x(), event->scenePos().y()))
        {
            this->_item = (ItemDrawable*)item;
            this->_item->setColor(QColor(Qt::darkBlue));
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
            message->setMessage(this->_item);
            this->sceneGo()->sendMessage(message);
            return true;
        }
    }
    return false;
}

bool ToolGoPointerExtend::mousePressStatusNullScene(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->_status = Status_Scene_Moving;
    this->graphicsView()->setCursor(Qt::ClosedHandCursor);
    this->graphicsView()->setDragMode(QGraphicsView::ScrollHandDrag);
    return true;
}

void ToolGoPointerExtend::mouseMoveStatusNull(QGraphicsSceneMouseEvent *event)
{
    if (!this->mouseMoveStatusNullSignal(event))
    {
        if (!this->mouseMoveStatusNullSignalAdjust(event))
        {
            event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                                       ((int)event->scenePos().y() / 10) * 10));
            if (!this->mouseMoveStatusNullItem(event))
            {
                this->mouseMoveStatusNullScene(event);
            }
        }
    }
}

bool ToolGoPointerExtend::mouseMoveStatusNullSignal(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> items;
    items = this->graphicsScene()->items(QRectF(event->scenePos().x() - 2, event->scenePos().y() - 2, 4, 4));
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR || item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoOperator *op = (ItemGoOperator*)items.at(i);
            GoOperator *model = op->model();
            for (int j = 0; j < model->output()->number(); ++j)
            {
                if (this->isAround(event->scenePos(), op->pos() + op->getOutputPosition(j)))
                {
                    this->graphicsView()->setCursor(Qt::CrossCursor);
                    return true;
                }
            }
        }
    }
    return false;
}

bool ToolGoPointerExtend::mouseMoveStatusNullSignalAdjust(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> items = this->graphicsScene()->items(QRectF(event->scenePos().x() - 100, event->scenePos().y() - 100, 200, 200));
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            ItemGoSignal *signal = (ItemGoSignal*)items.at(i);
            if (signal->isCornerLineSelectable(event->scenePos().x(), event->scenePos().y()))
            {
                this->graphicsView()->setCursor(Qt::SizeHorCursor);
                return true;
            }
        }
    }
    return false;
}

bool ToolGoPointerExtend::mouseMoveStatusNullItem(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> items = this->graphicsScene()->items(event->scenePos());
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable* item = (ItemDrawable*)items[i];
        if (item->moveable())
        {
            if (item->isSelectable(event->scenePos().x(), event->scenePos().y()))
            {
                this->graphicsView()->setCursor(Qt::SizeAllCursor);
                return true;
            }
        }
    }
    for (int i = 0; i < items.size(); ++i)
    {
        if (((ItemDrawable*)items[i])->isSelectable(event->scenePos().x(), event->scenePos().y()))
        {
            return true;
        }
    }
    return false;
}

bool ToolGoPointerExtend::mouseMoveStatusNullScene(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->graphicsView()->setCursor(Qt::OpenHandCursor);
    return true;
}

void ToolGoPointerExtend::mouseReleaseStatusNull(QGraphicsSceneMouseEvent *event)
{
    if (this->_item != 0L)
    {
        this->_item->setColor(QColor(Qt::black));
    }
    this->_item = 0L;
    QList<QGraphicsItem*> items = this->graphicsScene()->items(event->scenePos());
    for (int i = 0; i < items.size(); ++i)
    {
        if (((ItemDrawable*)items[i])->isSelectable(event->scenePos().x(), event->scenePos().y()))
        {
            this->_item = (ItemDrawable*)items[i];
            this->_item->setColor(QColor(Qt::darkBlue));
            break;
        }
    }
    ItemGoFactory::sendSelectionMessage(this->sceneGo(), this->_item);
}

void ToolGoPointerExtend::mouseMoveStatusItemMoving(QGraphicsSceneMouseEvent *event)
{
    event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                               ((int)event->scenePos().y() / 10) * 10));
    if (this->_item)
    {
        ((ItemMoveable*)this->_item)->move(event);
    }
    this->sceneGo()->viewGo()->editor()->setModified(true);
}

void ToolGoPointerExtend::mouseReleaseStatusItemMoving(QGraphicsSceneMouseEvent *event)
{
    event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                               ((int)event->scenePos().y() / 10) * 10));
    if (this->_item)
    {
        ((ItemMoveable*)this->_item)->stopMove(event);
        this->_item->setColor(QColor(Qt::darkBlue));
        ItemGoFactory::sendSelectionMessage(this->sceneGo(), this->_item);
    }
    this->graphicsView()->setCursor(Qt::ArrowCursor);
    this->_status = Status_Null;
}

void ToolGoPointerExtend::mouseReleaseStatusSceneMoving(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->_status = Status_Null;
    if (this->_item != 0L)
    {
        this->_item->setColor(QColor(Qt::black));
    }
    this->_item = 0L;
    ItemGoFactory::sendSelectionMessage(this->sceneGo(), this->_item);
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
}

void ToolGoPointerExtend::mouseMoveStatusSignalConnecting(QGraphicsSceneMouseEvent *event)
{
    this->_signal->setEndPosition(event->scenePos().x() - this->_signal->pos().x(),
                                          event->scenePos().y() - this->_signal->pos().y());
}

void ToolGoPointerExtend::mouseReleaseStatusSignalConnecting(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> items = this->graphicsScene()->items(QRectF(event->scenePos().x() - 100, event->scenePos().y() - 100, 200, 200));
    bool found = false;
    for (int i = 0; i < items.size() && !found; ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR || item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoOperator *op = (ItemGoOperator*)item;
            GoOperator *model = op->model();
            for (int j = 0; j < model->input()->number(); ++j)
            {
                if (op->input()->at(j) != 0L)
                {
                    continue;
                }
                if (isAround(event->scenePos(), op->pos() + op->getInputPosition(j)))
                {
                    this->_signal->end()->op = op;
                    this->_signal->end()->id = op->model()->realID();
                    this->_signal->end()->index = j;
                    this->_signal->end()->type = DefinationGoType::GO_OPERATOR_INPUT;
                    QPointF end = op->pos() + op->getInputPosition(j) - this->_signal->pos();
                    this->_signal->setEndPosition(end.x(), end.y());
                    this->_signal->start()->op->setSignal(this->_signal,
                                                              this->_signal->start()->type,
                                                              this->_signal->start()->index);
                    this->_signal->end()->op->setSignal(this->_signal,
                                                            this->_signal->end()->type,
                                                            this->_signal->end()->index);
                    if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
                    {
                        ((ItemGoMarkovOperator*)this->_signal->end()->op)->globalFeedbackExtend();
                    }
                    found = true;
                    break;
                }
            }
            for (int j = 0; j < model->subInput()->number(); ++j)
            {
                if (op->subInput()->at(j) != 0L)
                {
                    continue;
                }
                if (isAround(event->scenePos(), op->pos() + op->getSubInputPosition(j)))
                {
                    this->_signal->end()->op = op;
                    this->_signal->end()->index = j;
                    this->_signal->end()->type = DefinationGoType::GO_OPERATOR_SUBINPUT;
                    QPointF end = op->pos() + op->getSubInputPosition(j) - this->_signal->pos();
                    this->_signal->setEndPosition(end.x(), end.y());
                    this->_signal->start()->op->setSignal(this->_signal,
                                                              this->_signal->start()->type,
                                                              this->_signal->start()->index);
                    this->_signal->end()->op->setSignal(this->_signal,
                                                            this->_signal->end()->type,
                                                            this->_signal->end()->index);
                    if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
                    {
                        ((ItemGoMarkovOperator*)this->_signal->end()->op)->globalFeedbackExtend();
                    }
                    found = true;
                    break;
                }
            }
        }
    }
    if (!found)
    {
        delete this->_signal;
    }
    else
    {
        ItemGoFactory::sendSelectionMessage(this->sceneGo(), this->_signal);
        this->sceneGo()->viewGo()->editor()->setModified(true);
    }
    this->_signal = 0L;
    this->graphicsView()->setCursor(Qt::ArrowCursor);
    this->_status = Status_Null;
}

void ToolGoPointerExtend::mouseMoveStatusSignalAdjusting(QGraphicsSceneMouseEvent *event)
{
    event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                               ((int)event->scenePos().y() / 10) * 10));
    if (this->_item)
    {
        ItemGoSignal *signal = (ItemGoSignal*)this->_item;
        double len1 = event->scenePos().x() - signal->pos().x();
        double len2 = signal->endPos().x();
        double proportion = len1 / len2;
        signal->setCornerProportion(proportion);
        signal->update();
        this->sceneGo()->viewGo()->editor()->setModified(true);
    }
}

void ToolGoPointerExtend::mouseReleaseStatusSignalAdjusting(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->graphicsView()->setCursor(Qt::ArrowCursor);
    this->_status = Status_Null;
}
