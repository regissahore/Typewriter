#include "ParameterFactory.h"
#include "DefinationEditorSelectionType.h"
#include "ParameterGoText.h"
#include "ParameterGoSignal.h"
#include "ParameterGoOperator.h"
#include "ParameterGoMarkovOperator.h"
#include "ParameterGoMarkovEquivalent.h"
#include "ParameterGoMarkovCommonCause.h"

ParameterAbstract* ParameterFactory::produce(int type)
{
    ParameterAbstract* parameter = nullptr;
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
    default:
        break;
    }
    if (parameter == nullptr)
    {
        parameter = new ParameterAbstract();
    }
    return parameter;
}
