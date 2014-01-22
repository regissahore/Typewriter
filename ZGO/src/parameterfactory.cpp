#include "parameterfactory.h"
#include "definationeditorselectiontype.h"
#include "parametergotext.h"
#include "parametergosignal.h"
#include "parametergooperator.h"
#include "parametergomarkovoperator.h"
#include "parametergomarkovequivalent.h"
#include "parametergomarkovcommoncause.h"
#include "parametergomarkovcommoncause2.h"
#include "parametergomarkovchart.h"

ParameterAbstract* ParameterFactory::produce(int type)
{
    ParameterAbstract* parameter = 0L;
    switch (type)
    {
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR:
        parameter = new ParameterGOOperator();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL:
        parameter = new ParameterGOSignal();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_TEXT:
        parameter = new ParameterGOText();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR:
        parameter = new ParameterGOMarkovOperator();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT:
        parameter = new ParameterGOMarkovEquivalent();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE:
        parameter = new ParameterGOMarkovCommonCause();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE_2:
        parameter = new ParameterGOMarkovCommonCause2();
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_CHART:
        parameter = new ParameterGOMarkovChart();
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
