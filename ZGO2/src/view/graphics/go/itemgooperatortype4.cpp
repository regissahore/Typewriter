#include "itemgooperatortype4.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType4::ItemGOOperatorType4(QGraphicsItem *parent) : ItemGOSource(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_4);
    this->updateGraphic();
}
