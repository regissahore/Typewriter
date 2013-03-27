#include "toolgooperatorunfixedinput.h"
#include "scenego.h"
#include "gooperatorfactory.h"
#include "gooperator.h"
#include "messagefactory.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorUnfixedInput::ToolGOOperatorUnfixedInput(SceneGO *sceneGO) : ToolGOOperator(sceneGO)
{
}

/**
 * Activate.
 */
void ToolGOOperatorUnfixedInput::activate()
{
    this->getInputNumber();
}
