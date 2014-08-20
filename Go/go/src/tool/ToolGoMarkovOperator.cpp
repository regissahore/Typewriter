#include "ToolGoMarkovOperator.h"
#include "ItemGoMarkovOperator.h"
#include "DefinationEditorSelectionType.h"
#include "GoMarkovOperatorFactory.h"
#include "GoOperator.h"
#include "ItemGoMarkovEquivalent.h"
#include "GoMarkovOperator13.h"

ToolGoMarkovOperator::ToolGoMarkovOperator(SceneGo *sceneGo) : ToolGoOperator(sceneGo)
{
    this->_defaultToolType = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
}

void ToolGoMarkovOperator::activate(QGraphicsSceneMouseEvent *event)
{
    if (this->_isActivated)
    {
        this->setType(this->TypedItem::type());
    }
    this->_isActivated = true;
    this->_GoOperator->setPos(event->scenePos());
    switch (this->_GoOperator->model()->type())
    {
    case GoMarkovOperatorFactory::Operator_Type_2:
        this->getInputNumber();
        break;
    case GoMarkovOperatorFactory::Operator_Type_4:
        this->getOutputNumber();
        break;
    case GoMarkovOperatorFactory::Operator_Type_10:
        this->getInputNumber();
        break;
    case GoMarkovOperatorFactory::Operator_Type_11:
    case GoMarkovOperatorFactory::Operator_Type_11A:
        this->getInputNumber();
        break;
    case GoMarkovOperatorFactory::Operator_Type_12A:
        this->getOutputNumber();
        break;
    case GoMarkovOperatorFactory::Operator_Type_13:
        if (this->getInputNumber())
        {
            this->getOutputNumber();
        }
        break;
    case GoMarkovOperatorFactory::Operator_Type_13A:
    case GoMarkovOperatorFactory::Operator_Type_13B:
        if (this->getInputNumber())
        {
            if (this->getOutputNumber())
            {
                ((GoMarkovOperator13*)this->_GoOperator->model())->initRelation();
            }
        }
        break;
    case GoMarkovOperatorFactory::Operator_Type_14:
        this->getInputNumber();
        break;
    case GoMarkovOperatorFactory::Operator_Type_15A:
        this->getDualNumber();
        break;
    case GoMarkovOperatorFactory::Operator_Type_15B:
        this->getInputNumber();
        break;
    case GoMarkovOperatorFactory::Operator_Type_22:
    case GoMarkovOperatorFactory::Operator_Type_22A:
    case GoMarkovOperatorFactory::Operator_Type_22B:
        this->getOutputNumber();
        break;
    case GoMarkovOperatorFactory::Operator_Type_23:
        this->getInputNumber();
        break;
    case GoMarkovOperatorFactory::Operator_Type_Split:
        this->getOutputNumber();
        break;
    default:
        break;
    }
}

void ToolGoMarkovOperator::setType(const int type)
{
    this->TypedItem::setType(type);
    this->_GoOperator = new ItemGoMarkovOperator();
    switch (this->type())
    {
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_1:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_1);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_2:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_2);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_3:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_3);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_4:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_4);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_5:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_5);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_6:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_6);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_7:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_7);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_8:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_8);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_9);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9A:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_9A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9A1:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_9A1);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9A2:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_9A2);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9B:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_9B);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9B1:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_9B1);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9B2:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_9B2);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_10:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_10);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_11:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_11);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_11A:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_11A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_12:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_12);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_12A:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_12A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_13);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13A:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_13A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13B:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_13B);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_14:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_14);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_15);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15A:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_15A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15B:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_15B);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_16:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_16);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_17:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_17);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_18:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_18);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_18A:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_18A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_19:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_19);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_20:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_20);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_21:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_21);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_22);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22A:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_22A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22B:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_22B);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_23:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_23);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_SPLIT:
        this->_GoOperator->setModelType(GoMarkovOperatorFactory::Operator_Type_Split);
        break;
    }
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
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
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
            this->_GoOperator->model()->setId(i);
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
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
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
            this->_GoOperator->model()->setRealID(i);
            break;
        }
    }

    this->graphicsScene()->addItem(this->_GoOperator);
}
