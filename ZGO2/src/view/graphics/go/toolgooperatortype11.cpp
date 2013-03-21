#include "toolgooperatortype11.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorType11::ToolGOOperatorType11(SceneGO *sceneGO) : ToolGOOperatorUnfixedInput(sceneGO)
{
    this->_GOOperator = new ItemGOOperatorType11();
    this->_GOOperator->setVisible(false);
    this->graphicsScene()->addItem(this->_GOOperator);
}
