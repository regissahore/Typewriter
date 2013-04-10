#include "itemgomarkovoperator.h"
#include "definationeditorselectiontype.h"
#include "gomarkovoperatorfactory.h"
#include "gomarkovoperator.h"

ItemGOMarkovOperator::ItemGOMarkovOperator(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->TypedItem::setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR);
}

void ItemGOMarkovOperator::setType(int type)
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
