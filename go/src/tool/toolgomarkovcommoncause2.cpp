#include "ToolGoMarkovCommonCause2.h"
#include "GoMarkovOperator.h"
#include "ItemGoMarkovOperator.h"
#include "ItemGoMarkovCommonCause2.h"
#include "Message.h"
#include "MessageFactory.h"
#include "Messager.h"
#include "DefinationToolType.h"
#include "DefinationEditorSelectionType.h"
#include "SceneGo.h"
#include "GoMarkovCommonCause.h"
#include "ItemGoFactory.h"
#include "ViewGo.h"
#include "EditorGo.h"
#include "GoMarkovStatus.h"

ToolGoMarkovCommonCause2::ToolGoMarkovCommonCause2(SceneGo *sceneGo) : ToolGoAbstract(sceneGo)
{
    this->_status = Status_Selecting;
    this->_operatorList = new QVector<ItemGoMarkovOperator*>();
    this->_commonItem = 0L;
}

ToolGoMarkovCommonCause2::~ToolGoMarkovCommonCause2()
{
    if (this->_status != Status_Finished)
    {
        if (this->_commonItem != 0L)
        {
            ItemGoFactory::deleteItem(this->_commonItem);
        }
    }
    for (int i = 0; i < this->_operatorList->size(); ++i)
    {
        this->_operatorList->at(i)->setColor(Qt::black);
    }
    delete this->_operatorList;
}

void ToolGoMarkovCommonCause2::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_status == Status_Finishing)
    {
        this->_commonItem->setPos(event->scenePos());
    }
}

void ToolGoMarkovCommonCause2::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_status == Status_Selecting)
    {
        if (event->button() == Qt::LeftButton)
        {
            QList<QGraphicsItem*> items = this->graphicsScene()->items(event->scenePos());
            for (int i = 0; i < items.size(); ++i)
            {
                ItemDrawable* item = (ItemDrawable*)items[i];
                if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_Go_MARKOV_OPERATOR)
                {
                    this->addOperator((ItemGoMarkovOperator*)item);
                }
            }
        }
        else
        {
            this->_status = Status_Finishing;
            if (this->_operatorList->size() > 1)
            {
                this->_commonItem = new ItemGoMarkovCommonCause2();
                for (int i = 0; i < this->_operatorList->size(); ++i)
                {
                    this->_commonItem->operatorItems()->push_back(this->operatorList()->at(i));
                    this->_commonItem->model()->idList()->push_back(this->_operatorList->at(i)->model()->realID());
                    this->_commonItem->model()->operators()->push_back((GoMarkovOperator*)this->_operatorList->at(i)->model());
                    this->_operatorList->at(i)->setFatherCommonCause2(this->_commonItem);
                }
                GoMarkovOperator *op = (GoMarkovOperator*)this->_operatorList->at(0)->model();
                double totalLambda = 0.0;
                if (op->breakdownNum() >= 1)
                {
                    totalLambda += op->markovStatus1()->frequencyBreakdown().getValue(0);
                }
                if (op->breakdownNum() >= 2)
                {
                    totalLambda += op->markovStatus2()->frequencyBreakdown().getValue(0);
                }
                if (op->breakdownNum() >= 3)
                {
                    totalLambda += op->markovStatus3()->frequencyBreakdown().getValue(0);
                }
                if (op->breakdownNum() >= 4)
                {
                    totalLambda += op->markovStatus4()->frequencyBreakdown().getValue(0);
                }
                this->_commonItem->model()->setBreakdownTotal(totalLambda);
                this->sceneGo()->addItem(this->_commonItem);
                this->_commonItem->setPos(event->scenePos());
                this->_commonItem->updateBoundary();
            }
            else
            {
                QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
                message->paramInt = DefinationToolType::TOOL_TYPE_Go_MARKOV_POINTER_EXTEND;
                this->sceneGo()->sendMessage(message);
            }
        }
    }
    else if (this->_status == Status_Finishing)
    {
        if (event->button() == Qt::LeftButton)
        {
            this->_status = Status_Finished;
            this->sceneGo()->viewGo()->editor()->setModified(true);
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
            message->paramInt = DefinationToolType::TOOL_TYPE_Go_MARKOV_POINTER_EXTEND;
            this->sceneGo()->sendMessage(message);
        }
        else if (event->button() == Qt::RightButton)
        {
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
            message->paramInt = DefinationToolType::TOOL_TYPE_Go_MARKOV_POINTER_EXTEND;
            this->sceneGo()->sendMessage(message);
        }
    }
}

QVector<ItemGoMarkovOperator*>* ToolGoMarkovCommonCause2::operatorList() const
{
    return this->_operatorList;
}

void ToolGoMarkovCommonCause2::addOperator(ItemGoMarkovOperator* op)
{
    if (op->fatherCommonCause2() != 0L)
    {
        return;
    }
    for (int i = 0; i < this->_operatorList->size(); ++i)
    {
        if (this->_operatorList->at(i) == op)
        {
            this->_operatorList->at(i)->setColor(Qt::black);
            this->_operatorList->remove(i);
            return;
        }
    }
    this->_operatorList->push_back(op);
    op->setColor(Qt::darkBlue);
}
