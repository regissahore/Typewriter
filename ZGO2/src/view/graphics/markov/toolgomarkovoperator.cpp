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
    case GOMarkovOperatorFactory::Operator_Type_12A:
        this->getOutputNumber();
        break;
    case GOMarkovOperatorFactory::Operator_Type_13:
        if (this->getInputNumber())
        {
            this->getOutputNumber();
        }
        break;
    case GOMarkovOperatorFactory::Operator_Type_13A:
    case GOMarkovOperatorFactory::Operator_Type_13B:
        if (this->getInputNumber())
        {
            if (this->getOutputNumber())
            {
                ((GOMarkovOperator13*)this->_GOOperator->model())->initRelation();
            }
        }
        break;
    case GOMarkovOperatorFactory::Operator_Type_14:
        this->getInputNumber();
        break;
    case GOMarkovOperatorFactory::Operator_Type_15A:
        this->getDualNumber();
        break;
    case GOMarkovOperatorFactory::Operator_Type_15B:
        this->getInputNumber();
        break;
    case GOMarkovOperatorFactory::Operator_Type_22:
    case GOMarkovOperatorFactory::Operator_Type_22A:
    case GOMarkovOperatorFactory::Operator_Type_22B:
        this->getOutputNumber();
        break;
    case GOMarkovOperatorFactory::Operator_Type_23:
        this->getInputNumber();
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
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9_A1:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_9A1);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9_A2:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_9A2);
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
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_12_A:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_12A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_13);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13_A:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_13A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13_B:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_13B);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_14:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_14);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_15);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15_A:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_15A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15_B:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_15B);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_16:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_16);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_17:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_17);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_18:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_18);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_18_A:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_18A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_19:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_19);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_20:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_20);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_21:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_21);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_22);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22_A:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_22A);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22_B:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_22B);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_23:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_23);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_24:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_24);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_25:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_25);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_26:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_26);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_27:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_27);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_28:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_28);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_29:
        this->_GOOperator->setModelType(GOMarkovOperatorFactory::Operator_Type_29);
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
