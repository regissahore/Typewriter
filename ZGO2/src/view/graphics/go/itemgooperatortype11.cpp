#include "itemgooperatortype11.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType11::ItemGOOperatorType11(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_11);
    this->updateGraphic();
}
