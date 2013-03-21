#include "itemgooperatortype13.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType13::ItemGOOperatorType13(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_13);
    this->updateGraphic();
}
