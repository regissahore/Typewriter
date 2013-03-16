#include "controller/messageeditortype.h"

/**
 * 构造函数。
 */
MessageEditorType::MessageEditorType() : Message(), TypedItem()
{
    this->setName("Editor_Type");
}

/**
 * 析构函数。
 */
MessageEditorType::~MessageEditorType()
{
    if (this->_message)
    {
        delete (MessageContent*)this->_message;
    }
}

/**
 * 输出编辑器的类别。
 * @return 编辑器类别。
 */
QString MessageEditorType::toString()
{
    QString str = "";
    if (this->message() != 0L)
    {
        str += QString("Index: %1 ").arg(((MessageContent*)this->message())->index);
    }
    str += "Type: ";
    switch (this->type())
    {
    case DefinationEditorType::EDITOR_TYPE_NULL:
        str += "No editor. ";
    case DefinationEditorType::EDITOR_TYPE_WELCOME:
        str += "Welcom screen. ";
    case DefinationEditorType::EDITOR_TYPE_GO:
        str += "The GO Graph editor. ";
    default:
        str += "Undefined editor. ";
    }
    return str;
}

void MessageEditorType::setIndex(int index)
{
    this->setMessage(new MessageContent(index));
}
