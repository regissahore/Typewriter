#include "toolgooperatortype3.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorType3::ToolGOOperatorType3(SceneGO *sceneGO) : ToolGOOperator(sceneGO)
{
    this->_GOOperator = new ItemGOOperatorType3();
    this->_GOOperator->setVisible(false);
    this->graphicsScene()->addItem(this->_GOOperator);
}
