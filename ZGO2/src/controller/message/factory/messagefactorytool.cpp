#include "messagefactorytool.h"

/**
 * 构造函数。
 */
MessageFactoryTool::MessageFactoryTool() : MessageFactory()
{
}

/**
 * 生成工具相关的消息。
 * @param type 消息类型。
 * @return 消息内容。
 */
Message* MessageFactoryTool::produce(int type)
{
    Message *message = 0L;
    switch (type)
    {
    case TOOL_SELECTION:
        message = new MessageToolSelection();
    }
    return message;
}
