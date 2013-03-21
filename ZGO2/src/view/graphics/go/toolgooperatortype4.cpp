#include "toolgooperatortype4.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorType4::ToolGOOperatorType4(SceneGO *sceneGO) : ToolGOOperatorUnfixedOutput(sceneGO)
{
    this->_GOOperator = new ItemGOOperatorType4();
    this->_GOOperator->setVisible(false);
    this->graphicsScene()->addItem(this->_GOOperator);
    this->getOutputNumber();
}
