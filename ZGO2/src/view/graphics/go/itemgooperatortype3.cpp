#include "itemgooperatortype3.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType3::ItemGOOperatorType3(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_3);
    this->updateGraphic();
}
