#include "toolgofactory.h"
#include "toolgopointer.h"
#include "toolgomove.h"
#include "toolgozoom.h"
#include "toolgoselect.h"
#include "toolgotext.h"
#include "toolgooperator.h"
#include "toolgosignal.h"
#include "toolgopointerextend.h"
#include "toolgomarkovoperator.h"
#include "toolgomarkovequivalent.h"
#include "toolgomarkovpointerextend.h"
#include "toolgomarkovtext.h"
#include "toolgomarkovcommoncause.h"
#include "toolgomarkovcommoncause2.h"

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
    case DefinationToolType::TOOL_TYPE_GO_POINTER_EXTEND:
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
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND:
        tool = new ToolGOMarkovPointerExtend(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_1:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_2:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_3:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_4:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_5:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_6:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_7:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_8:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9A:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9A1:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9A2:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9B:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9B1:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9B2:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_10:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_11:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_11A:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_12:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_12A:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13A:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13B:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_14:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15A:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15B:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_16:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_17:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_18:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_18A:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_19:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_20:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_21:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22A:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22B:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_23:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_24:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_25:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_26:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_27:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_28:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_29:
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_SPLIT:
        tool = new ToolGOMarkovOperator(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_SIGNAL:
        tool = new ToolGOSignal(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_EQUIVALENT:
        tool = new ToolGOMarkovEquivalent(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_COMMON_CAUSE:
        tool = new ToolGOMarkovCommonCause(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_COMMON_CAUSE_2:
        tool = new ToolGOMarkovCommonCause2(sceneGO);
        break;
    case DefinationToolType::TOOL_TYPE_GO_MARKOV_TEXT:
        tool = new ToolGOMarkovText(sceneGO);
        break;
    }
    if (tool != 0L)
    {
        tool->setType(type);
    }
    return tool;
}
