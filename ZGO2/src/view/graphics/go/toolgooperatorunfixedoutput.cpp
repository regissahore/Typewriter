#include "toolgooperatorunfixedoutput.h"
#include "scenego.h"
#include "gooperatorfactory.h"
#include "gooperator.h"
#include "messagefactory.h"

ToolGOOperatorUnfixedOutput::ToolGOOperatorUnfixedOutput(SceneGO *sceneGO) : ToolGOOperator(sceneGO)
{
}

void ToolGOOperatorUnfixedOutput::activate()
{
    this->getOutputNumber();
}
