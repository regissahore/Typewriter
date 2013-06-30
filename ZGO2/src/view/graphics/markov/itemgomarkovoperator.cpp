#include "itemgomarkovoperator.h"
#include "definationeditorselectiontype.h"
#include "gomarkovoperatorfactory.h"
#include "gomarkovoperator.h"
#include "itemgomarkovequivalent.h"
#include "itemgomarkovcommoncause.h"
#include "gomarkovoperator1e1.h"

ItemGOMarkovOperator::ItemGOMarkovOperator(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->TypedItem::setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR);
    this->_fatherEquivalent = 0L;
    this->_fatherCommonCause = 0L;
}

ItemGOMarkovEquivalent* ItemGOMarkovOperator::fatherEquivalent() const
{
    return this->_fatherEquivalent;
}

ItemGOMarkovEquivalent* ItemGOMarkovOperator::rootEquivalent() const
{
    if (this->fatherEquivalent() != 0L)
    {
        ItemGOMarkovEquivalent *eq = this->fatherEquivalent();
        while (eq->fatherEquivalent() != 0L)
        {
            eq = eq->fatherEquivalent();
        }
        return eq;
    }
    return 0L;
}

void ItemGOMarkovOperator::setFatherEquivalent(ItemGOMarkovEquivalent* equivalent)
{
    this->_fatherEquivalent = equivalent;
}

ItemGOMarkovCommonCause* ItemGOMarkovOperator::fatherCommonCause() const
{
    return this->_fatherCommonCause;
}

void ItemGOMarkovOperator::setFatherCommonCause(ItemGOMarkovCommonCause* commonCause)
{
    this->_fatherCommonCause = commonCause;
}

void ItemGOMarkovOperator::move(QGraphicsSceneMouseEvent *event)
{
    this->ItemGOOperator::move(event);
    if (this->fatherEquivalent() != 0L)
    {
        this->fatherEquivalent()->updateBoundary();
    }
    if (this->fatherCommonCause() != 0L)
    {
        this->fatherCommonCause()->updateBoundary();
    }
}

void ItemGOMarkovOperator::setModelType(const int type)
{
    this->_model = GOMarkovOperatorFactory::produce(type);
    this->setModel(this->_model);
}

bool ItemGOMarkovOperator::tryOpen(QDomElement &root)
{
    if (root.tagName() != "operator")
    {
        return false;
    }
    this->setX(root.attribute("x", "0").toFloat());
    this->setY(root.attribute("y", "0").toFloat());
    int type = root.attribute("type").toInt();
    QDomElement element = root.firstChildElement();
    GOMarkovOperator *model;
    if (type == GOMarkovOperatorFactory::Operator_Type_1_E1)
    {
        model = new GOMarkovOperator1E1();
    }
    else
    {
        model = new GOMarkovOperator();
    }
    if (!model->tryOpen(element))
    {
        return false;
    }
    this->setModel(model);
    return true;
}
