#include "toolgomarkovcommoncause2.h"
#include "gomarkovoperator.h"
#include "itemgomarkovoperator.h"
#include "itemgomarkovcommoncause2.h"
#include "message.h"
#include "messagefactory.h"
#include "messager.h"
#include "definationtooltype.h"
#include "definationeditorselectiontype.h"
#include "scenego.h"
#include "gomarkovcommoncause.h"
#include "itemgofactory.h"
#include "viewgo.h"
#include "editorgo.h"
#include "gomarkovstatus.h"

ToolGOMarkovCommonCause2::ToolGOMarkovCommonCause2(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->_status = Status_Selecting;
    this->_operatorList = new QVector<ItemGOMarkovOperator*>();
    this->_commonItem = 0L;
}

ToolGOMarkovCommonCause2::~ToolGOMarkovCommonCause2()
{
    if (this->_status != Status_Finished)
    {
        if (this->_commonItem != 0L)
        {
            ItemGOFactory::deleteItem(this->_commonItem);
        }
    }
    for (int i = 0; i < this->_operatorList->size(); ++i)
    {
        this->_operatorList->at(i)->setColor(Qt::black);
    }
    delete this->_operatorList;
}

void ToolGOMarkovCommonCause2::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_status == Status_Finishing)
    {
        this->_commonItem->setPos(event->scenePos());
    }
}

void ToolGOMarkovCommonCause2::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_status == Status_Selecting)
    {
        if (event->button() == Qt::LeftButton)
        {
            QList<QGraphicsItem*> items = this->graphicsScene()->items(event->scenePos());
            for (int i = 0; i < items.size(); ++i)
            {
                ItemDrawable* item = (ItemDrawable*)items[i];
                if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
                {
                    this->addOperator((ItemGOMarkovOperator*)item);
                }
            }
        }
        else
        {
            this->_status = Status_Finishing;
            if (this->_operatorList->size() > 1)
            {
                this->_commonItem = new ItemGOMarkovCommonCause2();
                for (int i = 0; i < this->_operatorList->size(); ++i)
                {
                    this->_commonItem->operatorItems()->push_back(this->operatorList()->at(i));
                    this->_commonItem->model()->operators()->push_back((GOMarkovOperator*)this->_operatorList->at(i)->model());
                    this->_operatorList->at(i)->setFatherCommonCause2(this->_commonItem);
                }
                this->_commonItem->model()->setBreakdownTotal(((GOMarkovOperator*)this->_operatorList->at(0)->model())->markovStatus1()->frequencyBreakdown());
                this->sceneGO()->addItem(this->_commonItem);
                this->_commonItem->setPos(event->scenePos());
                this->_commonItem->updateBoundary();
            }
            else
            {
                Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
                message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
                this->sceneGO()->sendMessage(message);
            }
        }
    }
    else if (this->_status == Status_Finishing)
    {
        if (event->button() == Qt::LeftButton)
        {
            this->_status = Status_Finished;
            this->sceneGO()->viewGO()->editor()->setModified(true);
            Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
            message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
            this->sceneGO()->sendMessage(message);
        }
        else if (event->button() == Qt::RightButton)
        {
            Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
            message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
            this->sceneGO()->sendMessage(message);
        }
    }
}

QVector<ItemGOMarkovOperator*>* ToolGOMarkovCommonCause2::operatorList() const
{
    return this->_operatorList;
}

void ToolGOMarkovCommonCause2::addOperator(ItemGOMarkovOperator* op)
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
