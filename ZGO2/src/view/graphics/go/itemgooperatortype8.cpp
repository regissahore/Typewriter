#include "itemgooperatortype8.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType8::ItemGOOperatorType8(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_8);
    this->updateGraphic();
}
