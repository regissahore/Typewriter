#include "toolgomarkovoperator.h"
#include "itemgomarkovoperator.h"
#include "definationeditorselectiontype.h"
#include "gomarkovoperatorfactory.h"
#include "gooperator.h"
#include "itemgomarkovequivalent.h"
#include "gomarkovoperator13.h"

ToolGOMarkovOperator::ToolGOMarkovOperator(SceneGO *sceneGO) : ToolGOOperator(sceneGO)
{
    this->_defaultToolType = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
}

void ToolGOMarkovOperator::activate(QGraphicsSceneMouseEvent *event)
{
    this->_isActivated = true;
    this->_GOOperator->setPos(event->scenePos());
    switch (this->_GOOperator->model()->type())
    {
    case GOMarkovOperatorFactory::Operator_Type_2:
        this->getInputNumber();
        break;
    case GOMarkovOperatorFactory::Operator_Type_4:
        this->getOutputNumber();
        break;
    case GOMarkovOperatorFactory::Operator_Type_10:
        this->getInputNumber();
        break;
    case GOMarkovOperatorFactory::Operator_Type_11:
        this->getInputNumber();
        break;
    case GOMarkovOperatorFactory::Operator_Type_13:
        if (this->getInputNumber())
        {
            this->getOutputNumber();
        }
        break;
    case GOMarkovOperatorFactory::Operator_Type_14:
        this->getInputNumber();
        break;
    case GOMarkovOperatorFactory::Operator_Type_13_A:
    case GOMarkovOperatorFactory::Operator_Type_13_B:
        if (this->getInputNumber())
        {
            if (this->getOutputNumber())
            {
                ((GOMarkovOperator13*)this->_GOOperator->model())->initRelation();
            }
        }
        break;
    case GOMarkovOperatorFactory::Operator_Type_15_A:
        this->getDualNumber();
        break;
    default:
        break;
    }
}

void ToolGOMarkovOperator::setType(const int type)
{
    this->TypedItem::setType(type);
    this->_GOOperator = new ItemGOMarkovOperator();
    switch (this->type())
    {
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_1:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_1);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_2:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_2);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_3:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_3);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_4:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_4);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_5:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_5);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_6:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_6);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_7:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_7);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_8:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_8);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_9);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_10:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_10);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_11:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_11);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_12:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_12);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_13);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_14:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_14);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_15);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_16:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_16);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_17:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_17);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_1_E1:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_1_E1);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9_A1:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_9_A1);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9_A2:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_9_A2);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13_A:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_13_A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13_B:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_13_B);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15_A:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_15_A);
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
            ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)item;
            visit[op->model()->id()] = true;
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            ItemGOMarkovEquivalent *eq = (ItemGOMarkovEquivalent*)item;
            visit[eq->id()] = true;
        }
    }
    for (int i = 1; i <= items.size() + 1; ++i)
    {
        if (!visit[i])
        {
            this->_GOOperator->model()->setId(i);
            break;
        }
    }
    this->graphicsScene()->addItem(this->_GOOperator);
}
