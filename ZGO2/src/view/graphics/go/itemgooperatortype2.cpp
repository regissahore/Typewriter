#include "itemgooperatortype2.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType2::ItemGOOperatorType2(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_2);
    this->updateGraphic();
}
