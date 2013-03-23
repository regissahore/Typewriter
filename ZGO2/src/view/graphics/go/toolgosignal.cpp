#include "toolgosignal.h"
#include "itemgosignal.h"
#include "itemgooperator.h"
#include "gooperator.h"
#include "definationgotype.h"
#include "definationeditorselectiontype.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOSignal::ToolGOSignal(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->_tempSignal = new ItemGOSignal();
    this->_status = Status_Null;
}

/**
 * Destructor.
 */
ToolGOSignal::~ToolGOSignal()
{
    delete this->_tempSignal;
}

/**
 * Mouse press event.
 * @param event Mouse event.
 */
void ToolGOSignal::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> items = this->graphicsScene()->items(event->scenePos().x() - 2, event->scenePos().y() - 2, 4, 4);
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
        {
            ItemGOOperator *op = (ItemGOOperator*)item;
            GOOperator *model = op->model();
            for (int i = 0; i < model->input()->number(); ++i)
            {
                if (isAround(event->scenePos(), op->pos() + op->getInputPosition(i)))
                {
                    this->_status = Status_Adding;
                    this->_tempSignal->start()->op = op;
                    this->_tempSignal->start()->index = i;
                    this->_tempSignal->start()->type = DefinationGOType::GO_OPERATOR_INPUT;
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
                    this->_tempSignal->start()->type = DefinationGOType::GO_OPERATOR_OUTPUT;
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
                    this->_tempSignal->start()->type = DefinationGOType::GO_OPERATOR_SUBINPUT;
                    this->graphicsScene()->addItem(this->_tempSignal);
                    this->_tempSignal->setPos(op->pos() + op->getSubInputPosition(i));
                    return;
                }
            }
        }
    }
}

/**
 * Mouse move event.
 * @param event Mouse event.
 */
void ToolGOSignal::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_status == Status_Adding)
    {
        this->_tempSignal->setEndPosition(event->scenePos().x() - this->_tempSignal->pos().x(),
                                          event->scenePos().y() - this->_tempSignal->pos().y());
    }
    this->graphicsView()->setCursor(Qt::ArrowCursor);
    QList<QGraphicsItem*> items = this->graphicsScene()->items(event->scenePos().x() - 2, event->scenePos().y() - 2, 4, 4);
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
        {
            ItemGOOperator *op = (ItemGOOperator*)item;
            GOOperator *model = op->model();
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

/**
 * Mouse release event.
 * @param event Mouse event.
 */
void ToolGOSignal::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_status == Status_Adding)
    {
        this->_status = Status_Null;
        QList<QGraphicsItem*> items = this->graphicsScene()->items(event->scenePos().x() - 2, event->scenePos().y() - 2, 4, 4);
        for (int i = 0; i < items.size(); ++i)
        {
            ItemDrawable *item = (ItemDrawable*)items.at(i);
            if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
            {
                ItemGOOperator *op = (ItemGOOperator*)item;
                GOOperator *model = op->model();
                for (int i = 0; i < model->input()->number(); ++i)
                {
                    if (isAround(event->scenePos(), op->pos() + op->getInputPosition(i)))
                    {
                        this->_tempSignal->end()->op = op;
                        this->_tempSignal->end()->index = i;
                        this->_tempSignal->end()->type = DefinationGOType::GO_OPERATOR_INPUT;
                        QPointF end = op->pos() + op->getInputPosition(i) - this->_tempSignal->pos();
                        this->_tempSignal->setEndPosition(end.x(), end.y());
                        this->_tempSignal->start()->op->setSignal(this->_tempSignal,
                                                                  this->_tempSignal->start()->type,
                                                                  this->_tempSignal->start()->index);
                        this->_tempSignal->end()->op->setSignal(this->_tempSignal,
                                                                this->_tempSignal->end()->type,
                                                                this->_tempSignal->end()->index);
                        this->_tempSignal = new ItemGOSignal();
                        return;
                    }
                }
                for (int i = 0; i < model->output()->number(); ++i)
                {
                    if (isAround(event->scenePos(), op->pos() + op->getOutputPosition(i)))
                    {
                        this->_tempSignal->end()->op = op;
                        this->_tempSignal->end()->index = i;
                        this->_tempSignal->end()->type = DefinationGOType::GO_OPERATOR_OUTPUT;
                        QPointF end = op->pos() + op->getOutputPosition(i) - this->_tempSignal->pos();
                        this->_tempSignal->setEndPosition(end.x(), end.y());
                        this->_tempSignal->start()->op->setSignal(this->_tempSignal,
                                                                  this->_tempSignal->start()->type,
                                                                  this->_tempSignal->start()->index);
                        this->_tempSignal->end()->op->setSignal(this->_tempSignal,
                                                                this->_tempSignal->end()->type,
                                                                this->_tempSignal->end()->index);
                        this->_tempSignal = new ItemGOSignal();
                        return;
                    }
                }
                for (int i = 0; i < model->subInput()->number(); ++i)
                {
                    if (isAround(event->scenePos(), op->pos() + op->getSubInputPosition(i)))
                    {
                        this->_tempSignal->end()->op = op;
                        this->_tempSignal->end()->index = i;
                        this->_tempSignal->end()->type = DefinationGOType::GO_OPERATOR_SUBINPUT;
                        QPointF end = op->pos() + op->getSubInputPosition(i) - this->_tempSignal->pos();
                        this->_tempSignal->setEndPosition(end.x(), end.y());
                        this->_tempSignal->start()->op->setSignal(this->_tempSignal,
                                                                  this->_tempSignal->start()->type,
                                                                  this->_tempSignal->start()->index);
                        this->_tempSignal->end()->op->setSignal(this->_tempSignal,
                                                                this->_tempSignal->end()->type,
                                                                this->_tempSignal->end()->index);
                        this->_tempSignal = new ItemGOSignal();
                        return;
                    }
                }
            }
        }
    }
}

/**
 * Whether two points is close enough.
 * @param pos1 Point 1.
 * @param pos2 Point 2.
 * @return Returns true if two points are close, otherwise false.
 */
bool ToolGOSignal::isAround(QPointF pos1, QPointF pos2)
{
    return (pos1.x() - pos2.x()) * (pos1.x() - pos2.x()) +
            (pos1.y() - pos2.y()) * (pos1.y() - pos2.y()) <= 6;
}
