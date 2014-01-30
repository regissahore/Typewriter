#include "ParameterFactory.h"
#include "DefinationEditorSelectionType.h"
#include "ParameterGoText.h"
#include "ParameterGoSignal.h"
#include "ParameterGoOperator.h"
#include "ParameterGoMarkovOperator.h"
#include "ParameterGoMarkovEquivalent.h"
#include "ParameterGoMarkovCommonCause.h"
#include "ParameterGoMarkovCommonCause2.h"
#include "ParameterGoMarkovChart.h"

ParameterAbstract* ParameterFactory::produce(int type)
{
    ParameterAbstract* parameter = 0L;
    switch (type)
    {
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR:
        parameter = new ParameterGoOperator();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL:
        parameter = new ParameterGoSignal();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_TEXT:
        parameter = new ParameterGoText();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR:
        parameter = new ParameterGoMarkovOperator();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT:
        parameter = new ParameterGoMarkovEquivalent();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE:
        parameter = new ParameterGoMarkovCommonCause();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE_2:
        parameter = new ParameterGoMarkovCommonCause2();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_CHART:
        parameter = new ParameterGoMarkovChart();
        break;
    default:
        break;
    }
    if (parameter == 0L)
    {
        parameter = new ParameterAbstract();
    }
    return parameter;
}
