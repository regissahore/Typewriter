#include "toolgomarkovtext.h"
#include "messagefactory.h"
#include "definationtooltype.h"

ToolGOMarkovText::ToolGOMarkovText(SceneGO *sceneGO) : ToolGOText(sceneGO)
{
    this->_defaultToolType = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
}
