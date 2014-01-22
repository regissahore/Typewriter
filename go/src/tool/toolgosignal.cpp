#include "ToolGoSignal.h"
#include "ItemGoSignal.h"
#include "ItemGoOperator.h"
#include "GoOperator.h"
#include "DefinationGoType.h"
#include "DefinationEditorSelectionType.h"
#include "GoInput.h"
#include "GoOutput.h"

ToolGoSignal::ToolGoSignal(SceneGo *sceneGo) : ToolGoAbstract(sceneGo)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->_tempSignal = new ItemGoSignal();
    this->_status = Status_Null;
}

ToolGoSignal::~ToolGoSignal()
{
    delete this->_tempSignal;
}

void ToolGoSignal::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> items = this->graphicsScene()->items(QRectF(event->scenePos().x() - 2, event->scenePos().y() - 2, 4, 4));
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_Go_OPERATOR)
        {
            ItemGoOperator *op = (ItemGoOperator*)item;
            GoOperator *model = op->model();
            for (int i = 0; i < model->input()->number(); ++i)
            {
                if (isAround(event->scenePos(), op->pos() + op->getInputPosition(i)))
                {
                    this->_status = Status_Adding;
                    this->_tempSignal->start()->op = op;
                    this->_tempSignal->start()->index = i;
                    this->_tempSignal->start()->type = DefinationGoType::Go_OPERATOR_INPUT;
                    this->graphicsScene()->addItem(this->_tempSignal);
                    this->_tempSignal->setPos(op->pos() + op->getInputPosition(i));
                    return;
                }
            }
            for (int i = 0; i < model->output()->number(); ++i)
            {
                if (isAround(event->scenePos(), op->pos() + op->getOutputPosition(i)))
                {
                    this->_status = Status_Adding;
                    this->_tempSignal->start()->op = op;
                    this->_tempSignal->start()->index = i;
                    this->_tempSignal->start()->type = DefinationGoType::Go_OPERATOR_OUTPUT;
                    this->graphicsScene()->addItem(this->_tempSignal);
                    this->_tempSignal->setPos(op->pos() + op->getOutputPosition(i));
                    return;
                }
            }
            for (int i = 0; i < model->subInput()->number(); ++i)
            {
                if (isAround(event->scenePos(), op->pos() + op->getSubInputPosition(i)))
                {
                    this->_status = Status_Adding;
                    this->_tempSignal->start()->op = op;
                    this->_tempSignal->start()->index = i;
                    this->_tempSignal->start()->type = DefinationGoType::Go_OPERATOR_SUBINPUT;
                    this->graphicsScene()->addItem(this->_tempSignal);
                    this->_tempSignal->setPos(op->pos() + op->getSubInputPosition(i));
                    return;
                }
            }
        }
    }
}

void ToolGoSignal::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_status == Status_Adding)
    {
        this->_tempSignal->setEndPosition(event->scenePos().x() - this->_tempSignal->pos().x(),
                                          event->scenePos().y() - this->_tempSignal->pos().y());
    }
    this->graphicsView()->setCursor(Qt::ArrowCursor);
    QList<QGraphicsItem*> items = this->graphicsScene()->items(QRectF(event->scenePos().x() - 2, event->scenePos().y() - 2, 4, 4));
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_Go_OPERATOR)
        {
            ItemGoOperator *op = (ItemGoOperator*)item;
            GoOperator *model = op->model();
            for (int i = 0; i < model->input()->number(); ++i)
            {
                if (isAround(event->scenePos(), op->pos() + op->getInputPosition(i)))
                {
                    this->graphicsView()->setCursor(Qt::PointingHandCursor);
                    return;
                }
            }
            for (int i = 0; i < model->output()->number(); ++i)
            {
                if (isAround(event->scenePos(), op->pos() + op->getOutputPosition(i)))
                {
                    this->graphicsView()->setCursor(Qt::PointingHandCursor);
                    return;
                }
            }
            for (int i = 0; i < model->subInput()->number(); ++i)
            {
                if (isAround(event->scenePos(), op->pos() + op->getSubInputPosition(i)))
                {
                    this->graphicsView()->setCursor(Qt::PointingHandCursor);
                    return;
                }
            }
        }
    }
}

void ToolGoSignal::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_status == Status_Adding)
    {
        this->_status = Status_Null;
        QList<QGraphicsItem*> items = this->graphicsScene()->items(QRectF(event->scenePos().x() - 2, event->scenePos().y() - 2, 4, 4));
        for (int i = 0; i < items.size(); ++i)
        {
            ItemDrawable *item = (ItemDrawable*)items.at(i);
            if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_Go_OPERATOR)
            {
                ItemGoOperator *op = (ItemGoOperator*)item;
                GoOperator *model = op->model();
                for (int i = 0; i < model->input()->number(); ++i)
                {
                    if (isAround(event->scenePos(), op->pos() + op->getInputPosition(i)))
                    {
                        this->_tempSignal->end()->op = op;
                        this->_tempSignal->end()->index = i;
                        this->_tempSignal->end()->type = DefinationGoType::Go_OPERATOR_INPUT;
                        QPointF end = op->pos() + op->getInputPosition(i) - this->_tempSignal->pos();
                        this->_tempSignal->setEndPosition(end.x(), end.y());
                        this->_tempSignal->start()->op->setSignal(this->_tempSignal,
                                                                  this->_tempSignal->start()->type,
                                                                  this->_tempSignal->start()->index);
                        this->_tempSignal->end()->op->setSignal(this->_tempSignal,
                                                                this->_tempSignal->end()->type,
                                                                this->_tempSignal->end()->index);
                        this->_tempSignal = new ItemGoSignal();
                        return;
                    }
                }
                for (int i = 0; i < model->output()->number(); ++i)
                {
                    if (isAround(event->scenePos(), op->pos() + op->getOutputPosition(i)))
                    {
                        this->_tempSignal->end()->op = op;
                        this->_tempSignal->end()->index = i;
                        this->_tempSignal->end()->type = DefinationGoType::Go_OPERATOR_OUTPUT;
                        QPointF end = op->pos() + op->getOutputPosition(i) - this->_tempSignal->pos();
                        this->_tempSignal->setEndPosition(end.x(), end.y());
                        this->_tempSignal->start()->op->setSignal(this->_tempSignal,
                                                                  this->_tempSignal->start()->type,
                                                                  this->_tempSignal->start()->index);
                        this->_tempSignal->end()->op->setSignal(this->_tempSignal,
                                                                this->_tempSignal->end()->type,
                                                                this->_tempSignal->end()->index);
                        this->_tempSignal = new ItemGoSignal();
                        return;
                    }
                }
                for (int i = 0; i < model->subInput()->number(); ++i)
                {
                    if (isAround(event->scenePos(), op->pos() + op->getSubInputPosition(i)))
                    {
                        this->_tempSignal->end()->op = op;
                        this->_tempSignal->end()->index = i;
                        this->_tempSignal->end()->type = DefinationGoType::Go_OPERATOR_SUBINPUT;
                        QPointF end = op->pos() + op->getSubInputPosition(i) - this->_tempSignal->pos();
                        this->_tempSignal->setEndPosition(end.x(), end.y());
                        this->_tempSignal->start()->op->setSignal(this->_tempSignal,
                                                                  this->_tempSignal->start()->type,
                                                                  this->_tempSignal->start()->index);
                        this->_tempSignal->end()->op->setSignal(this->_tempSignal,
                                                                this->_tempSignal->end()->type,
                                                                this->_tempSignal->end()->index);
                        this->_tempSignal = new ItemGoSignal();
                        return;
                    }
                }
            }
        }
        this->_tempSignal->setEndPosition(0, 0);
        this->graphicsScene()->removeItem(this->_tempSignal);
    }
}

bool ToolGoSignal::isAround(QPointF pos1, QPointF pos2)
{
    return (pos1.x() - pos2.x()) * (pos1.x() - pos2.x()) +
            (pos1.y() - pos2.y()) * (pos1.y() - pos2.y()) <= 6;
}
