#include "itemgooperatortype6.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType6::ItemGOOperatorType6(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_6);
    this->updateGraphic();
}
