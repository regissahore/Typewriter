#include "toolgooperatortype1.h"

/**
 * Construtor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorType1::ToolGOOperatorType1(SceneGO *sceneGO) : ToolGOOperator(sceneGO)
{
    this->_GOOperator = new ItemGOOperatorType1();
    this->_GOOperator->setVisible(false);
    this->graphicsScene()->addItem(this->_GOOperator);
}
