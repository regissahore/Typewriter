#include <QVector>
#include "scenego.h"
#include "toolgopointerextend.h"
#include "definationgotype.h"
#include "definationeditorselectiontype.h"
#include "itemdrawable.h"
#include "itemmoveable.h"
#include "itemgooperator.h"
#include "itemgosignal.h"
#include "itemgofactory.h"
#include "gooperator.h"
#include "gosignal.h"
#include "goinput.h"
#include "gooutput.h"
#include "messagefactory.h"

ToolGOPointerExtend::ToolGOPointerExtend(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->_item = 0L;
    this->_signal = 0L;
    this->_status = Status_Null;
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->graphicsView()->setCursor(Qt::ArrowCursor);
}

ToolGOPointerExtend::~ToolGOPointerExtend()
{
    this->ToolGOAbstract::~ToolGOAbstract();
    if (this->_item != 0L)
    {
        this->_item->setColor(QColor(Qt::black));
    }
}

void ToolGOPointerExtend::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

void ToolGOPointerExtend::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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

void ToolGOPointerExtend::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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

void ToolGOPointerExtend::keyReleaseEvent(QKeyEvent *event)
{
    switch (this->_status)
    {
    case Status_Null:
        if (event->key() == Qt::Key_Delete)
        {
            if (this->_item != 0L)
            {
                ItemGOFactory::deleteItem(this->_item);
                this->_item = 0L;
            }
        }
        break;
    default:
        break;
    }
}

bool ToolGOPointerExtend::isAround(QPointF pos1, QPointF pos2)
{
    return (pos1.x() - pos2.x()) * (pos1.x() - pos2.x()) +
            (pos1.y() - pos2.y()) * (pos1.y() - pos2.y()) <= 81;
}

void ToolGOPointerExtend::mousePressStatusNull(QGraphicsSceneMouseEvent *event)
{
    if (!this->mousePressStatusNullSignal(event))
    {
        if (!this->mousePressStatusNullSignalAdjust(event))
        {
            if (!this->mousePressStatusNullItem(event))
            {
                this->mousePressStatusNullScene(event);
            }
        }
    }
}

bool ToolGOPointerExtend::mousePressStatusNullSignal(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> items = this->graphicsScene()->items(QRectF(event->scenePos().x() - 100, event->scenePos().y() - 100, 200, 200));
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR || item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOOperator *op = (ItemGOOperator*)items.at(i);
            GOOperator *model = op->model();
            for (int j = 0; j < model->output()->number(); ++j)
            {
                if (this->isAround(event->scenePos(), op->pos() + op->getOutputPosition(j)))
                {
                    this->_status = Status_Signal_Connecting;
                    this->_signal = new ItemGOSignal();
                    items = this->graphicsScene()->items();
                    this->_signal->model()->setId(model->id());
                    this->_signal->start()->id = op->model()->id();
                    this->_signal->start()->op = op;
                    this->_signal->start()->index = j;
                    this->_signal->start()->type = DefinationGOType::GO_OPERATOR_OUTPUT;
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

bool ToolGOPointerExtend::mousePressStatusNullSignalAdjust(QGraphicsSceneMouseEvent *event)
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
            ItemGOSignal *signal = (ItemGOSignal*)items.at(i);
            if (signal->isCornerLineSelectable(event->scenePos().x(), event->scenePos().y()))
            {
                this->_status = Status_Signal_Adjusting;
                this->_item = signal;
                this->_item->setColor(QColor(Qt::darkBlue));
                Message *message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
                message->setMessage(this->_item);
                this->sceneGO()->sendMessage(message);
                this->graphicsView()->setCursor(Qt::SizeHorCursor);
                return true;
            }
        }
    }
    return false;
}

bool ToolGOPointerExtend::mousePressStatusNullItem(QGraphicsSceneMouseEvent *event)
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
            Message *message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
            message->setMessage(this->_item);
            this->sceneGO()->sendMessage(message);
            return true;
        }
    }
    return false;
}

bool ToolGOPointerExtend::mousePressStatusNullScene(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->_status = Status_Scene_Moving;
    this->graphicsView()->setCursor(Qt::ClosedHandCursor);
    this->graphicsView()->setDragMode(QGraphicsView::ScrollHandDrag);
    return true;
}

void ToolGOPointerExtend::mouseMoveStatusNull(QGraphicsSceneMouseEvent *event)
{
    if (!this->mouseMoveStatusNullSignal(event))
    {
        if (!this->mouseMoveStatusNullSignalAdjust(event))
        {
            if (!this->mouseMoveStatusNullItem(event))
            {
                this->mouseMoveStatusNullScene(event);
            }
        }
    }
}

bool ToolGOPointerExtend::mouseMoveStatusNullSignal(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> items;
    items = this->graphicsScene()->items(QRectF(event->scenePos().x() - 2, event->scenePos().y() - 2, 4, 4));
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR || item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOOperator *op = (ItemGOOperator*)items.at(i);
            GOOperator *model = op->model();
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

bool ToolGOPointerExtend::mouseMoveStatusNullSignalAdjust(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> items = this->graphicsScene()->items(QRectF(event->scenePos().x() - 100, event->scenePos().y() - 100, 200, 200));
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            ItemGOSignal *signal = (ItemGOSignal*)items.at(i);
            if (signal->isCornerLineSelectable(event->scenePos().x(), event->scenePos().y()))
            {
                this->graphicsView()->setCursor(Qt::SizeHorCursor);
                return true;
            }
        }
    }
    return false;
}

bool ToolGOPointerExtend::mouseMoveStatusNullItem(QGraphicsSceneMouseEvent *event)
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

bool ToolGOPointerExtend::mouseMoveStatusNullScene(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->graphicsView()->setCursor(Qt::OpenHandCursor);
    return true;
}

void ToolGOPointerExtend::mouseReleaseStatusNull(QGraphicsSceneMouseEvent *event)
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
    ItemGOFactory::sendSelectionMessage(this->sceneGO(), this->_item);
}

void ToolGOPointerExtend::mouseMoveStatusItemMoving(QGraphicsSceneMouseEvent *event)
{
    if (this->_item)
    {
        ((ItemMoveable*)this->_item)->move(event);
    }
}

void ToolGOPointerExtend::mouseReleaseStatusItemMoving(QGraphicsSceneMouseEvent *event)
{
    if (this->_item)
    {
        ((ItemMoveable*)this->_item)->stopMove(event);
        this->_item->setColor(QColor(Qt::darkBlue));
        ItemGOFactory::sendSelectionMessage(this->sceneGO(), this->_item);
    }
    this->graphicsView()->setCursor(Qt::ArrowCursor);
    this->_status = Status_Null;
}

void ToolGOPointerExtend::mouseReleaseStatusSceneMoving(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->_status = Status_Null;
    if (this->_item != 0L)
    {
        this->_item->setColor(QColor(Qt::black));
    }
    this->_item = 0L;
    ItemGOFactory::sendSelectionMessage(this->sceneGO(), this->_item);
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
}

void ToolGOPointerExtend::mouseMoveStatusSignalConnecting(QGraphicsSceneMouseEvent *event)
{
    this->_signal->setEndPosition(event->scenePos().x() - this->_signal->pos().x(),
                                          event->scenePos().y() - this->_signal->pos().y());
}

void ToolGOPointerExtend::mouseReleaseStatusSignalConnecting(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> items = this->graphicsScene()->items(QRectF(event->scenePos().x() - 100, event->scenePos().y() - 100, 200, 200));
    bool found = false;
    for (int i = 0; i < items.size() && !found; ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR || item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOOperator *op = (ItemGOOperator*)item;
            GOOperator *model = op->model();
            for (int j = 0; j < model->input()->number(); ++j)
            {
                if (model->input()->signal()->at(j) != 0L)
                {
                    continue;
                }
                if (isAround(event->scenePos(), op->pos() + op->getInputPosition(j)))
                {
                    this->_signal->end()->op = op;
                    this->_signal->end()->id = op->model()->id();
                    this->_signal->end()->index = j;
                    this->_signal->end()->type = DefinationGOType::GO_OPERATOR_INPUT;
                    QPointF end = op->pos() + op->getInputPosition(j) - this->_signal->pos();
                    this->_signal->setEndPosition(end.x(), end.y());
                    this->_signal->start()->op->setSignal(this->_signal,
                                                              this->_signal->start()->type,
                                                              this->_signal->start()->index);
                    this->_signal->end()->op->setSignal(this->_signal,
                                                            this->_signal->end()->type,
                                                            this->_signal->end()->index);
                    found = true;
                    break;
                }
            }
            for (int j = 0; j < model->subInput()->number(); ++j)
            {
                if (model->subInput()->signal()->at(j) != 0L)
                {
                    continue;
                }
                if (isAround(event->scenePos(), op->pos() + op->getSubInputPosition(j)))
                {
                    this->_signal->end()->op = op;
                    this->_signal->end()->index = j;
                    this->_signal->end()->type = DefinationGOType::GO_OPERATOR_SUBINPUT;
                    QPointF end = op->pos() + op->getSubInputPosition(j) - this->_signal->pos();
                    this->_signal->setEndPosition(end.x(), end.y());
                    this->_signal->start()->op->setSignal(this->_signal,
                                                              this->_signal->start()->type,
                                                              this->_signal->start()->index);
                    this->_signal->end()->op->setSignal(this->_signal,
                                                            this->_signal->end()->type,
                                                            this->_signal->end()->index);
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
        ItemGOFactory::sendSelectionMessage(this->sceneGO(), this->_signal);
    }
    this->_signal = 0L;
    this->graphicsView()->setCursor(Qt::ArrowCursor);
    this->_status = Status_Null;
}

void ToolGOPointerExtend::mouseMoveStatusSignalAdjusting(QGraphicsSceneMouseEvent *event)
{
    if (this->_item)
    {
        ItemGOSignal *signal = (ItemGOSignal*)this->_item;
        double len1 = event->scenePos().x() - signal->pos().x();
        double len2 = signal->endPos().x();
        double proportion = len1 / len2;
        signal->setCornerProportion(proportion);
        signal->update();
    }
}

void ToolGOPointerExtend::mouseReleaseStatusSignalAdjusting(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->graphicsView()->setCursor(Qt::ArrowCursor);
    this->_status = Status_Null;
}
