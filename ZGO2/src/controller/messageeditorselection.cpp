#include "controller/messageeditorselection.h"

/**
 * 构造函数。
 */
MessageEditorSelection::MessageEditorSelection() : Message(), TypedItem()
{
    this->setName("Editor_Selection");
}

/**
 * 输出编辑器选择内容。
 * @return 选择内容。
 */
QString MessageEditorSelection::toString()
{
    QString str = "Type: ";
    switch (this->type())
    {
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR:
        str += "GO operator. ";
        if (this->message())
        {
            str += QString("Operator Type: %1 ID: %2").
                    arg(((GOOperator*)this->message())->type()).
                    arg(((GOOperator*)this->message())->id());
        }
        break;
    case DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL:
        str += "GO signal. ";
        break;
    default:
        return "Undefined selection. ";
    }
    return str;
}
