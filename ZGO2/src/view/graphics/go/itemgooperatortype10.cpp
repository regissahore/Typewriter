#include "itemgooperatortype10.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType10::ItemGOOperatorType10(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_10);
    this->updateGraphic();
}
