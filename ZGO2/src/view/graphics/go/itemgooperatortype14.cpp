#include "itemgooperatortype14.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType14::ItemGOOperatorType14(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_14);
    this->updateGraphic();
}
