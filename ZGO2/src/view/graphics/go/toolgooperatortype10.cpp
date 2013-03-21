#include "toolgooperatortype10.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorType10::ToolGOOperatorType10(SceneGO *sceneGO) : ToolGOOperatorUnfixedInput(sceneGO)
{
    this->_GOOperator = new ItemGOOperatorType10();
    this->_GOOperator->setVisible(false);
    this->graphicsScene()->addItem(this->_GOOperator);
    this->getInputNumber();
}
