#include "itemgooperatortype12.h"
#include "gooperatorfactory.h"
#include "gooperator.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType12::ItemGOOperatorType12(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_12);
    this->updateGraphic();
}
