#include "controller/messagefactoryeditor.h"

/**
 * 构造函数。
 */
MessageFactoryEditor::MessageFactoryEditor() : MessageFactory()
{
}

/**
 * 产生消息。
 * @param type 消息类型。
 */
Message* MessageFactoryEditor::produceMessage(int type)
{
    Message* message = 0L;
    switch (type)
    {
    case EDITOR_TYPE:
        message = new MessageEditorType();
        break;
    case EDITOR_SELECTION:
        message = new MessageEditorSelection();
    }
    return message;
}
