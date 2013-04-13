#include "parameterfactory.h"
#include "definationeditorselectiontype.h"
#include "parametergotext.h"
#include "parametergosignal.h"
#include "parametergooperator.h"
#include "parametergomarkovoperator.h"
#include "parametergomarkovequivalent.h"

/**
 * Produce a abstract parameter widget.
 * @param type @see DefinationEditorSelectionType
 * @return Returns empty parameter widget if the type does not exist.
 */
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
    default:
        break;
    }
    if (parameter == 0L)
    {
        parameter = new ParameterAbstract();
    }
    return parameter;
}
