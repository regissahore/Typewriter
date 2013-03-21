#include "itemgooperatortype5.h"
#include "gooperatorfactory.h"
#include "gooperator.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperatorType5::ItemGOOperatorType5(QGraphicsItem *parent) : ItemGOSource(parent)
{
    this->_model = GOOperatorFactory::produce(GOOperatorFactory::Operator_Type_5);
    this->updateGraphic();
}
