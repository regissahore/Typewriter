#include "itemgooperatortype1.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType1::ItemGOOperatorType1(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_1);
    this->updateGraphic();
}
