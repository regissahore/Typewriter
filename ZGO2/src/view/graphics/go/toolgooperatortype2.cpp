#include "toolgooperatortype2.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorType2::ToolGOOperatorType2(SceneGO *sceneGO) : ToolGOOperatorUnfixedInput(sceneGO)
{
    this->_GOOperator = new ItemGOOperatorType2();
    this->_GOOperator->setVisible(false);
    this->graphicsScene()->addItem(this->_GOOperator);
}
