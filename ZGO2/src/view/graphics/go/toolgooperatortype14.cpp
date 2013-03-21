#include "toolgooperatortype14.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorType14::ToolGOOperatorType14(SceneGO *sceneGO) : ToolGOOperatorUnfixedInput(sceneGO)
{
    this->_GOOperator = new ItemGOOperatorType14();
    this->_GOOperator->setVisible(false);
    this->graphicsScene()->addItem(this->_GOOperator);
}
