#include <QtAlgorithms>
#include "ToolGoSelect.h"
#include "ItemGoOperator.h"
#include "ItemGoSignal.h"
#include "ItemGoFactory.h"
#include "DefinationEditorSelectionType.h"
#include "ItemGoMarkovOperator.h"
#include "GoMarkovOperator.h"
#include "SceneGo.h"
#include "ItemGoMarkovCommonCause.h"
#include "ItemGoMarkovCommonCause2.h"
#include "ItemGoMarkovEquivalent.h"
#include "GoMarkovCommonCause.h"
#include "GoMarkovEquivalent.h"
#include "ItemGoText.h"
#include "MessageFactory.h"
#include "Messager.h"
#include "ViewGo.h"
#include "EditorGo.h"

ToolGoSelect::ToolGoSelect(SceneGo *sceneGo) : ToolGoAbstract(sceneGo)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->_selection = new ItemSelection();
    this->graphicsScene()->addItem(this->_selection);
    this->_selection->setVisible(false);
    this->_status = Status_Null;
    this->graphicsView()->setCursor(Qt::ArrowCursor);
}

ToolGoSelect::~ToolGoSelect()
{
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ((ItemDrawable*)this->_items.at(i))->setColor(Qt::black);
    }
    this->_items.clear();
    delete this->_selection;
}

void ToolGoSelect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                               ((int)event->scenePos().y() / 10) * 10));
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

void ToolGoSelect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                               ((int)event->scenePos().y() / 10) * 10));
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
        this->sceneGo()->viewGo()->editor()->setModified(true);
        break;
    default:
        break;
    }
}

void ToolGoSelect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                               ((int)event->scenePos().y() / 10) * 10));
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

void ToolGoSelect::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        ItemGoFactory::deleteItems(this->_items);
        this->_items.clear();
        this->sceneGo()->viewGo()->editor()->setModified(true);
    }
    else if (event->key() == Qt::Key_C)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            this->copy();
        }
        this->sceneGo()->viewGo()->editor()->setModified(true);
    }
    else if (event->key() == Qt::Key_A)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            this->selectAll();
        }
    }
    else if (event->key() == Qt::Key_G)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            if (event->modifiers() & Qt::ShiftModifier)
            {
                this->unsetGlobalFeedback();
            }
            else
            {
                this->setGlobalFeedback();
            }
        }
        this->sceneGo()->viewGo()->editor()->setModified(true);
    }
    else if (event->key() == Qt::Key_P)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            if (event->modifiers() & Qt::ShiftModifier)
            {
                this->setHideParameter();
            }
            else
            {
                this->setShowParameter();
            }
        }
        this->sceneGo()->viewGo()->editor()->setModified(true);
    }
}

void ToolGoSelect::selectAll()
{
    QList<QGraphicsItem*> items = this->graphicsScene()->items();
    if (items.size() > 2)
    {
        //计算操作符的位置范围。
        int left = 0, right = 0;
        int top = 0, bottom = 0;
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

void ToolGoSelect::copy()
{
    //寻找出现过的操作符中最大的Real ID。
    int maxId = 0;
    QList<QGraphicsItem*> items = this->graphicsScene()->items();
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable* item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
            if (op->model()->realID() > maxId)
            {
                maxId = op->model()->realID();
            }
        }
    }
    maxId += 1;
    //寻找选中的操作符中最小的Real ID。
    int minSelectedId = 0x7fffffff;
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)this->_items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
            if (op->model()->realID() < minSelectedId)
            {
                minSelectedId = op->model()->realID();
            }
        }
    }
    int increaseId = maxId - minSelectedId;
    //复制操作符。
    QVector<ItemGoMarkovOperator*> newOps;
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)this->_items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
            ItemGoMarkovOperator *newOp = op->copy();
            newOp->model()->setRealID(newOp->model()->realID() + increaseId);
            newOp->setX(op->x() + 100);
            newOp->setY(op->y() + 100);
            newOps.push_back(newOp);
            this->sceneGo()->addItem(newOp);
        }
    }
    //复制信号流。
    QVector<ItemGoSignal*> newSignals;
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)this->_items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            ItemGoSignal *signal = (ItemGoSignal*)item;
            ItemGoSignal *newSignal = signal->copy();
            newSignal->start()->id += increaseId;
            newSignal->end()->id += increaseId;
            int find = 0;
            for (int j = 0; j < newOps.size(); ++j)
            {
                item = (ItemDrawable*)newOps.at(j);
                if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
                {
                    ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
                    if (op->model()->realID() == newSignal->start()->id)
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
                    ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
                    if (op->model()->realID() == newSignal->end()->id)
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
                this->sceneGo()->addItem(newSignal);
                newSignal->updatePosition();
            }
            else
            {
                delete newSignal;
            }
        }
    }
    //复制共因失效1。
    QVector<ItemGoMarkovCommonCause*> newCommons;
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ItemDrawable* item = (ItemDrawable*)this->_items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
        {
            ItemGoMarkovCommonCause *common = (ItemGoMarkovCommonCause*)item;
            ItemGoMarkovCommonCause *newCommon = common->copy();
            for (int j = 0; j < newCommon->model()->idList()->size(); ++j)
            {
                (*newCommon->model()->idList())[j] += increaseId;
            }
            int find = 0;
            for (int j = 0; j < newOps.size(); ++j)
            {
                for (int k = 0; k < newCommon->model()->idList()->size(); ++k)
                {
                    if (newOps[j]->model()->realID() == newCommon->model()->idList()->at(k))
                    {
                        (*newCommon->operatorItems())[k] = newOps[j];
                        (*newCommon->model()->operators())[k] = (GoMarkovOperator*)newOps[j]->model();
                        ++find;
                        break;
                    }
                }
            }
            if (find == newCommon->model()->idList()->size())
            {
                for (int j = 0; j < newCommon->operatorItems()->size(); ++j)
                {
                    newCommon->operatorItems()->at(j)->setFatherCommonCause(newCommon);
                }
                newCommons.push_back(newCommon);
                this->sceneGo()->addItem(newCommon);
                newCommon->updateBoundary();
            }
        }
    }
    //复制共因失效2。
    QVector<ItemGoMarkovCommonCause2*> fatherCommons;
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ItemDrawable* item = (ItemDrawable*)this->_items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator* op = (ItemGoMarkovOperator*)item;
            if (op->fatherCommonCause2() != nullptr)
            {
                bool flag = true;
                for (int j = 0; j < fatherCommons.size(); ++j)
                {
                    if (fatherCommons[j] == op->fatherCommonCause2())
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    fatherCommons.push_back(op->fatherCommonCause2());
                }
            }
        }
    }
    QVector<ItemGoMarkovCommonCause2*> newCommons2;
    for (int i = 0; i < fatherCommons.size(); ++i)
    {
        ItemGoMarkovCommonCause2 *common = fatherCommons[i];
        ItemGoMarkovCommonCause2 *newCommon = common->copy();
        for (int j = 0; j < newCommon->model()->idList()->size(); ++j)
        {
            (*newCommon->model()->idList())[j] += increaseId;
        }
        int find = 0;
        for (int j = 0; j < newOps.size(); ++j)
        {
            for (int k = 0; k < newCommon->model()->idList()->size(); ++k)
            {
                if (newOps[j]->model()->realID() == newCommon->model()->idList()->at(k))
                {
                    (*newCommon->operatorItems())[k] = newOps[j];
                    (*newCommon->model()->operators())[k] = (GoMarkovOperator*)newOps[j]->model();
                    ++find;
                    break;
                }
            }
        }
        if (find == newCommon->model()->idList()->size())
        {
            for (int j = 0; j < newCommon->operatorItems()->size(); ++j)
            {
                newCommon->operatorItems()->at(j)->setFatherCommonCause2(newCommon);
            }
            newCommons2.push_back(newCommon);
            this->sceneGo()->addItem(newCommon);
            newCommon->updateBoundary();
        }
    }
    //文字的复制。
    QVector<ItemGoText*> newTexts;
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ItemDrawable* item = (ItemDrawable*)this->_items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_TEXT)
        {
            ItemGoText *text = (ItemGoText*)item;
            ItemGoText *newText = text->copy();
            newText->setX(text->x() + 100);
            newText->setY(text->y() + 100);
            newTexts.push_back(newText);
            this->sceneGo()->addItem(newText);
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
    for (int i = 0; i < newCommons.size(); ++i)
    {
        this->_items.push_back(newCommons[i]);
    }
    for (int i = 0; i < newCommons2.size(); ++i)
    {
        this->_items.push_back(newCommons2[i]);
    }
    for (int i = 0; i < newTexts.size(); ++i)
    {
        this->_items.push_back(newTexts[i]);
    }
    for (int i = 0; i < this->_items.size(); ++i)
    {
        ((ItemDrawable*)this->_items.at(i))->setColor(Qt::darkBlue);
    }
}

void ToolGoSelect::setGlobalFeedback()
{
    for (int i = 0; i < this->_items.size(); ++i)
    {
        if (((ItemDrawable*)this->_items[i])->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_items[i];
            GoMarkovOperator *op = (GoMarkovOperator*)item->model();
            op->setIsGlobalFeedback(true);
            item->update();
        }
        else if (((ItemDrawable*)this->_items[i])->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            ItemGoSignal *item = (ItemGoSignal*)this->_items[i];
            GoSignal *signal = item->model();
            signal->setIsGlobalFeedback(true);
            item->update();
        }
    }
}

void ToolGoSelect::unsetGlobalFeedback()
{
    for (int i = 0; i < this->_items.size(); ++i)
    {
        if (((ItemDrawable*)this->_items[i])->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_items[i];
            GoMarkovOperator *op = (GoMarkovOperator*)item->model();
            op->setIsGlobalFeedback(false);
            item->update();
        }
        else if (((ItemDrawable*)this->_items[i])->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            ItemGoSignal *item = (ItemGoSignal*)this->_items[i];
            GoSignal *signal = item->model();
            signal->setIsGlobalFeedback(false);
            item->update();
        }
    }
}

void ToolGoSelect::setShowParameter()
{
    for (int i = 0; i < this->_items.size(); ++i)
    {
        if (((ItemDrawable*)this->_items[i])->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_items[i];
            item->setIsDrawParameter(true);
            item->update();
        }
    }
}

void ToolGoSelect::setHideParameter()
{
    for (int i = 0; i < this->_items.size(); ++i)
    {
        if (((ItemDrawable*)this->_items[i])->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_items[i];
            item->setIsDrawParameter(false);
            item->update();
        }
    }
}
