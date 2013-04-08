#include "toolgofactory.h"
#include "toolgopointer.h"
#include "toolgomove.h"
#include "toolgozoom.h"
#include "toolgoselect.h"
#include "toolgotext.h"
#include "toolgooperator.h"
#include "toolgosignal.h"
#include "toolgopointerextend.h"

/**
 * Produce a instantiated GO tool.
 * @param sceneGO The pointer to the SceneGO entity.
 * @param type The type of the tool. @see DefinationToolType
 * @return The instantiated tool, if the type of the tool is not exist, an empty pointer will be returned.
 */
ToolGOAbstract* ToolGOFactory::produce(SceneGO *sceneGO, const int type)
{
    ToolGOAbstract *tool = 0L;
    switch (type)
    {
    case DefinationToolType::TOOL_TYPE_COMMON_MOVE:
        tool = new ToolGOMove(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_COMMON_POINTER:
        tool = new ToolGOPointer(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_COMMON_SELECT:
        tool = new ToolGOSelect(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_COMMON_ZOOM:
        tool = new ToolGOZoom(sceneGO);
        break;
    case DefinationToolType::TOOLTYPE_GO_POINTER_EXTEND:
        tool = new ToolGOPointerExtend(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_TEXT:
        tool = new ToolGOText(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_1:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_2:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_3:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_4:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_5:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_6:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_7:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_8:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_9:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_10:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_11:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_12:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_13:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_14:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_15:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_16:
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_17:
        tool = new ToolGOOperator(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_SIGNAL:
        tool = new ToolGOSignal(sceneGO);
        break;
    }
    if (tool != 0L)
    {
        tool->setType(type);
    }
    return tool;
}
