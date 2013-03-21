#include "itemgooperatortype15.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType15::ItemGOOperatorType15(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_15);
    this->updateGraphic();
}
