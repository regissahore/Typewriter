#include "itemgomarkovoperator.h"
#include "definationeditorselectiontype.h"
#include "gomarkovoperatorfactory.h"
#include "gomarkovoperator.h"
#include "itemgomarkovequivalent.h"

ItemGOMarkovOperator::ItemGOMarkovOperator(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->TypedItem::setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR);
    this->_fatherEquivalent = 0L;
}

ItemGOMarkovEquivalent* ItemGOMarkovOperator::fatherEquivalent() const
{
    return this->_fatherEquivalent;
}

void ItemGOMarkovOperator::setFatherEquivalent(ItemGOMarkovEquivalent* equivalent)
{
    this->_fatherEquivalent = equivalent;
}

void ItemGOMarkovOperator::move(QGraphicsSceneMouseEvent *event)
{
    this->ItemGOOperator::move(event);
    if (this->fatherEquivalent() != 0L)
    {
        this->fatherEquivalent()->updateBoundary();
    }
}

void ItemGOMarkovOperator::setModelType(const int type)
{
    this->_model = GOMarkovOperatorFactory::produce(type);
    this->updateGraphic();
}

bool ItemGOMarkovOperator::tryOpen(QDomElement &root)
{
    if (root.tagName() != "operator")
    {
        return false;
    }
    this->setX(root.attribute("x", "0").toFloat());
    this->setY(root.attribute("y", "0").toFloat());
    QDomElement element = root.firstChildElement();
    GOMarkovOperator *model = new GOMarkovOperator();
    if (!model->tryOpen(element))
    {
        return false;
    }
    this->setModel(model);
    return true;
}
