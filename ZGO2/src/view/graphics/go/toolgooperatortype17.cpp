#include "toolgooperatortype17.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorType17::ToolGOOperatorType17(SceneGO *sceneGO) : ToolGOOperator(sceneGO)
{
    this->_GOOperator = new ItemGOOperatorType17();
    this->_GOOperator->setVisible(false);
    this->graphicsScene()->addItem(this->_GOOperator);
}
