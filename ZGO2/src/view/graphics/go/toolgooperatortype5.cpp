#include "toolgooperatortype5.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorType5::ToolGOOperatorType5(SceneGO *sceneGO) : ToolGOOperator(sceneGO)
{
    this->_GOOperator = new ItemGOOperatorType5();
    this->_GOOperator->setVisible(false);
    this->graphicsScene()->addItem(this->_GOOperator);
}
