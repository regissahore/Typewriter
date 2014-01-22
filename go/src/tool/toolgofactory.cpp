#include "ToolGoFactory.h"
#include "ToolGoPointer.h"
#include "ToolGoMove.h"
#include "ToolGoZoom.h"
#include "ToolGoSelect.h"
#include "ToolGoText.h"
#include "ToolGoOperator.h"
#include "ToolGoSignal.h"
#include "ToolGoPointerExtend.h"
#include "ToolGoMarkovOperator.h"
#include "ToolGoMarkovEquivalent.h"
#include "ToolGoMarkovPointerExtend.h"
#include "ToolGoMarkovText.h"
#include "ToolGoMarkovCommonCause.h"
#include "ToolGoMarkovCommonCause2.h"

ToolGoAbstract* ToolGoFactory::produce(SceneGo *sceneGo, const int type)
{
    ToolGoAbstract *tool = 0L;
    switch (type)
    {
    case DefinationToolType::TOOL_TYPE_COMMON_MOVE:
        tool = new ToolGoMove(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_COMMON_POINTER:
        tool = new ToolGoPointer(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_COMMON_SELECT:
        tool = new ToolGoSelect(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_COMMON_ZOOM:
        tool = new ToolGoZoom(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_Go_POINTER_EXTEND:
        tool = new ToolGoPointerExtend(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_Go_TEXT:
        tool = new ToolGoText(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_1:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_2:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_3:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_4:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_5:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_6:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_7:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_8:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_9:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_10:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_11:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_12:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_13:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_14:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_15:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_16:
    case DefinationToolType::TOOL_TYPE_Go_OPERATOR_17:
        tool = new ToolGoOperator(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_POINTER_EXTEND:
        tool = new ToolGoMarkovPointerExtend(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_1:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_2:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_3:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_4:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_5:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_6:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_7:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_8:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_9:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_9A:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_9A1:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_9A2:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_9B:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_9B1:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_9B2:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_10:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_11:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_11A:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_12:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_12A:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_13:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_13A:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_13B:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_14:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_15:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_15A:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_15B:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_16:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_17:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_18:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_18A:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_19:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_20:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_21:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_22:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_22A:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_22B:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_23:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_24:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_25:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_26:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_27:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_28:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_29:
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_OPERATOR_SPLIT:
        tool = new ToolGoMarkovOperator(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_Go_SIGNAL:
        tool = new ToolGoSignal(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_EQUIVALENT:
        tool = new ToolGoMarkovEquivalent(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_COMMON_CAUSE:
        tool = new ToolGoMarkovCommonCause(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_COMMON_CAUSE_2:
        tool = new ToolGoMarkovCommonCause2(sceneGo);
        break;
    case DefinationToolType::TOOL_TYPE_Go_MARKOV_TEXT:
        tool = new ToolGoMarkovText(sceneGo);
        break;
    }
    if (tool != 0L)
    {
        tool->setType(type);
    }
    return tool;
}
