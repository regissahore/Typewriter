#include "toolgooperatortype13.h"
#include "scenego.h"
#include "gooperator.h"
#include "messagefactory.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorType13::ToolGOOperatorType13(SceneGO *sceneGO) : ToolGOOperator(sceneGO)
{
    this->_GOOperator = new ItemGOOperatorType13();
    this->_GOOperator->setVisible(false);
    this->graphicsScene()->addItem(this->_GOOperator);
}

/**
 * Activate.
 */
void ToolGOOperatorType13::activate()
{
    this->getInputNumber();
    this->getOutputNumber();
}
