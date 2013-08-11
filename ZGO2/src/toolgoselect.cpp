#include <QtAlgorithms>
#include "toolgoselect.h"
#include "itemgooperator.h"
#include "itemgosignal.h"
#include "itemgofactory.h"
#include "definationeditorselectiontype.h"
#include "itemgomarkovoperator.h"
#include "gomarkovoperator.h"
#include "scenego.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOSelect::ToolGOSelect(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->_selection = new ItemSelection();
    this->graphicsScene()->addItem(this->_selection);
    this->_selection->setVisible(false);
    this->_status = Status_Null;
    this->graphicsView()->setCursor(Qt::ArrowCursor);
}

/**
 * Clear.
 */
ToolGOSelect::~ToolGOSelect()
{
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ((ItemDrawable*)this->_items.at(i))->setColor(Qt::black);
    }
    this->_items.clear();
    delete this->_selection;
}

/**
 * Mouse press event.
 * @param event Mouse event.
 */
void ToolGOSelect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->_status)
    {
    case Status_Null:
        this->_status = Status_Selecting;
        this->_selection->setPos(QPoint(event->scenePos().x(),
                                        event->scenePos().y()));
        this->_selection->setEnd(QPoint(0, 0));
        this->_selection->setVisible(true);
        break;
    case Status_Selected:
        if (this->_selection->isInside(event->scenePos().x(),
                                       event->scenePos().y()))
        {
            this->_status = Status_Moving;
            for (int i = 0; i < this->_items.size(); ++i)
            {
                if (((ItemDrawable*)this->_items[i])->moveable())
                {
                    ((ItemMoveable*)this->_items[i])->startMove(event);
                }
            }
            this->_selection->startMove(event);
        }
        else
        {
            this->_status = Status_Null;
            for (int i = 0; i < this->_items.size(); ++i)
            {
                ((ItemDrawable*)this->_items.at(i))->setColor(Qt::black);
            }
            this->_items.clear();
            this->mousePressEvent(event);
        }
        break;
    default:
        break;
    }
}

/**
 * Mouse move event.
 * @param event Mouse event.
 */
void ToolGOSelect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->_status)
    {
    case Status_Selecting:
        this->_selection->setEnd(QPoint(event->scenePos().x() - this->_selection->pos().x(),
                                        event->scenePos().y() - this->_selection->pos().y()));
        this->_selection->update();
        break;
    case Status_Selected:
        if (this->_selection->isInside(event->scenePos().x(), event->scenePos().y()))
        {
            this->graphicsView()->setCursor(Qt::SizeAllCursor);
        }
        else
        {
            this->graphicsView()->setCursor(Qt::ArrowCursor);
        }
        break;
    case Status_Moving:
        for (int i = 0; i < this->_items.size(); ++i)
        {
            if (((ItemDrawable*)this->_items[i])->moveable())
            {
                ((ItemMoveable*)this->_items[i])->move(event);
            }
        }
        this->_selection->move(event);
        break;
    default:
        break;
    }
}

/**
 * Mouse release event.
 * @param event Mouse event.
 */
void ToolGOSelect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem *> items;
    float x, y, width, height;
    switch (this->_status)
    {
    case Status_Selecting:
        this->_status = Status_Selected;
        if (this->_selection->end().x() >= 0)
        {
            x = this->_selection->pos().x();
            width = this->_selection->end().x();
        }
        else
        {
            x = this->_selection->pos().x() + this->_selection->end().x();
            width = -this->_selection->end().x();
        }
        if (this->_selection->end().y() >= 0)
        {
            y = this->_selection->pos().y();
            height = this->_selection->end().y();
        }
        else
        {
            y = this->_selection->pos().y() + this->_selection->end().y();
            height = -this->_selection->end().y();
        }
        items = this->graphicsScene()->items(QRectF(x, y, width, height),
                                             Qt::IntersectsItemBoundingRect);
        for (int i = 0; i < items.size(); ++i)
        {
            if (items[i] == this->_selection)
            {
                continue;
            }
            if (((ItemDrawable*)items[i])->isSelectable(this->_selection->pos().x(),
                                                      this->_selection->pos().y(),
                                                      this->_selection->end().x(),
                                                      this->_selection->end().y()))
            {
                this->_items.push_back(items[i]);
            }
        }
        for (int i = 0; i < this->_items.size(); ++i)
        {
            ((ItemDrawable*)this->_items.at(i))->setColor(Qt::darkBlue);
        }
        break;
    case Status_Moving:
        for (int i = 0; i < this->_items.size(); ++i)
        {
            if (((ItemDrawable*)this->_items[i])->moveable())
            {
                ((ItemMoveable*)this->_items[i])->stopMove(event);
            }
        }
        this->_selection->stopMove(event);
        this->_status = Status_Selected;
        break;
    default:
        break;
    }
    items.clear();
}

/**
 * Key Release event.
 * @param event Key event.
 */
void ToolGOSelect::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        ItemGOFactory::deleteItems(this->_items);
        this->_items.clear();
    }
    else if (event->key() == Qt::Key_C)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            this->copy();
        }
    }
    else if (event->key() == Qt::Key_A)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            this->selectAll();
        }
    }
}

void ToolGOSelect::selectAll()
{
    QList<QGraphicsItem*> items = this->graphicsScene()->items();
    if (items.size() > 2)
    {
        //计算操作符的位置范围。
        int left, right;
        int top, bottom;
        bool flag = true;
        this->_items.clear();
        for (int i = 0; i < items.size(); ++i)
        {
            ItemDrawable* item = (ItemDrawable*)items[i];
            if (item->TypedItem::type() != DefinationEditorSelectionType::EDITOR_SELECTION_EMPTY)
            {
                if (flag)
                {
                    left = item->x();
                    right = item->x();
                    top = item->y();
                    bottom = item->y();
                    flag = false;
                }
                else
                {
                    if (item->x() < left)
                    {
                        left = item->x();
                    }
                    if (item->x() > right)
                    {
                        right = item->x();
                    }
                    if (item->y() < top)
                    {
                        top = item->y();
                    }
                    if (item->y() > bottom)
                    {
                        bottom = item->y();
                    }
                }
                this->_items.push_back(item);
                item->setColor(Qt::darkBlue);
            }
        }
        left -= 50;
        right += 50;
        top -= 50;
        bottom += 50;
        this->_selection->setPos(left, top);
        this->_selection->setEnd(QPoint(right - left, bottom - top));
        this->_selection->setVisible(true);
    }
}

void ToolGOSelect::copy()
{
    //寻找出现过的操作符中最大的ID。
    int maxId = 0;
    QList<QGraphicsItem*> items = this->graphicsScene()->items();
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable* item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)item;
            if (op->model()->id() > maxId)
            {
                maxId = op->model()->id();
            }
        }
    }
    maxId += 1;
    //寻找选中的操作符中最小的ID。
    int minSelectedId = 0x7fffffff;
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)this->_items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)item;
            if (op->model()->id() < minSelectedId)
            {
                minSelectedId = op->model()->id();
            }
        }
    }
    if (minSelectedId == 0x7fffffff)
    {
        return;
    }
    int increaseId = maxId - minSelectedId;
    //复制操作符。
    QVector<ItemGOMarkovOperator*> newOps;
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)this->_items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)item;
            ItemGOMarkovOperator *newOp = op->copy();
            newOp->model()->setId(newOp->model()->id() + increaseId);
            newOp->setX(op->x() + 100);
            newOp->setY(op->y() + 100);
            newOps.push_back(newOp);
            this->sceneGO()->addItem(newOp);
        }
    }
    //复制信号流。
    QVector<ItemGOSignal*> newSignals;
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)this->_items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            ItemGOSignal *signal = (ItemGOSignal*)item;
            ItemGOSignal *newSignal = signal->copy();
            newSignal->start()->id += increaseId;
            newSignal->end()->id += increaseId;
            int find = 0;
            for (int j = 0; j < newOps.size(); ++j)
            {
                item = (ItemDrawable*)newOps.at(j);
                if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
                {
                    ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)item;
                    if (op->model()->id() == newSignal->start()->id)
                    {
                        newSignal->start()->op = op;
                        newSignal->start()->op->setSignal(newSignal,
                                                          newSignal->start()->type,
                                                          newSignal->start()->index);
                        ++find;
                        break;
                    }
                }
            }
            for (int j = 0; j < newOps.size(); ++j)
            {
                item = (ItemDrawable*)newOps.at(j);
                if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
                {
                    ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)item;
                    if (op->model()->id() == newSignal->end()->id)
                    {
                        newSignal->end()->op = op;
                        newSignal->end()->op->setSignal(newSignal,
                                                        newSignal->end()->type,
                                                        newSignal->end()->index);
                        ++find;
                        break;
                    }
                }
            }
            if (find == 2)
            {
                newSignals.push_back(newSignal);
                this->sceneGO()->addItem(newSignal);
                newSignal->updatePosition();
            }
            else
            {
                delete newSignal;
            }
        }
    }
    //更换选择内容。
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ((ItemDrawable*)this->_items.at(i))->setColor(Qt::black);
    }
    this->_items.clear();
    this->_selection->setX(this->_selection->x() + 100);
    this->_selection->setY(this->_selection->y() + 100);
    for (int i = 0; i< newOps.size(); ++i)
    {
        this->_items.push_back(newOps[i]);
    }
    for (int i = 0; i < newSignals.size(); ++i)
    {
        this->_items.push_back(newSignals[i]);
    }
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ((ItemDrawable*)this->_items.at(i))->setColor(Qt::darkBlue);
    }
}
