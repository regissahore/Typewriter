#include "toolgofactory.h"

/**
 * Produce a instantiated GO tool.
 * @param sceneGO The pointer to the SceneGO entity.
 * @param type The type of the tool. @see DefinationToolType
 * @return The instantiated tool, if the type of the tool is not exist, an empty pointer will be returned.
 */
ToolGOAbstract* ToolGOFactory::produce(SceneGO *sceneGO, int type)
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
        break;
    case DefinationToolType::TOOL_TYPE_COMMON_ZOOM:
        tool = new ToolGOZoom(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_TEXT:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_1:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_2:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_3:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_4:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_5:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_6:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_7:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_8:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_9:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_10:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_11:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_12:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_13:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_14:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_15:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_16:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_17:
        break;
    case DefinationToolType::TOOL_TYPE_GO_SINGAL:
        break;
    }
    if (tool != 0L)
    {
        tool->setType(type);
    }
    return tool;
}
