#include "toolgofactory.h"

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
    case DefinationToolType::TOOL_TYPE_GO_TEXT:
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_1:
        tool = new ToolGOOperatorType1(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_2:
        tool = new ToolGOOperatorType2(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_3:
        tool = new ToolGOOperatorType3(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_4:
        tool = new ToolGOOperatorType4(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_5:
        tool = new ToolGOOperatorType5(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_6:
        tool = new ToolGOOperatorType6(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_7:
        tool = new ToolGOOperatorType7(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_8:
        tool = new ToolGOOperatorType8(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_9:
        tool = new ToolGOOperatorType9(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_10:
        tool = new ToolGOOperatorType10(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_11:
        tool = new ToolGOOperatorType11(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_12:
        tool = new ToolGOOperatorType12(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_13:
        tool = new ToolGOOperatorType13(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_14:
        tool = new ToolGOOperatorType14(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_15:
        tool = new ToolGOOperatorType15(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_16:
        tool = new ToolGOOperatorType16(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_17:
        tool = new ToolGOOperatorType17(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_SINGAL:
        tool = new ToolGOSignal(sceneGO);
        break;
    }
    if (tool != 0L)
    {
        tool->setType(type);
    }
    return tool;
}
