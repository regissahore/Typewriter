#include "messageeditortype.h"

/**
 * 构造函数。
 */
MessageEditorType::MessageEditorType() : Message()
{
    this->setName("Editor_Type");
}

/**
 * 输出编辑器的类别。
 * @return 编辑器类别。
 */
QString MessageEditorType::toString()
{
    QString str = "";
    if (this->message() == 0L)
    {
        str = "No editor selected. ";
    }
    else
    {
        str = "Type: ";
        EditorAbstract* editor = (EditorAbstract*) this->message();
        switch (editor->type())
        {
        case DefinationEditorType::EDITOR_TYPE_WELCOME:
            str += "Welcome Screen; ";
            break;
        case DefinationEditorType::EDITOR_TYPE_GO:
            str += "GO Graph Editor; ";
            break;
        default:
            str += "Undefined Editor; ";
            break;
        }
        str += "Name: " + editor->name() + "; ";
        str += "Path: " + editor->path() + ". ";
    }
    return str;
}
