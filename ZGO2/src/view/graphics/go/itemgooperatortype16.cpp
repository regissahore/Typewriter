#include "itemgooperatortype16.h"
#include "gooperatorfactory.h"
#include "gooperator.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType16::ItemGOOperatorType16(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_16);
    this->updateGraphic();
}
