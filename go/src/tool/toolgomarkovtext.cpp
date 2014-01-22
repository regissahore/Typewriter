#include "ToolGoMarkovText.h"
#include "MessageFactory.h"
#include "DefinationToolType.h"

ToolGoMarkovText::ToolGoMarkovText(SceneGo *sceneGo) : ToolGoText(sceneGo)
{
    this->_defaultToolType = DefinationToolType::TOOL_TYPE_Go_MARKOV_POINTER_EXTEND;
}
