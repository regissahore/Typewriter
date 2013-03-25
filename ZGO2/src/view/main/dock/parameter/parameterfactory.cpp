#include "parameterfactory.h"
#include "definationeditorselectiontype.h"

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
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL:
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_TEXT:
        break;
    }
    if (parameter == 0L)
    {
        parameter = new ParameterAbstract();
    }
    return parameter;
}
