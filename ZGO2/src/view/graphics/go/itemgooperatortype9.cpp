#include "itemgooperatortype9.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType9::ItemGOOperatorType9(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_9);
    this->updateGraphic();
}
