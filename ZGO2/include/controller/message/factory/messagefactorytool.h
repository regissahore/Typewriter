#ifndef MESSAGEFACTORYTOOL_H
#define MESSAGEFACTORYTOOL_H
/**
 * 选择工具的消息工厂。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "messagefactory.h"
#include "messagetoolselection.h"

class MessageFactoryTool : public MessageFactory
{
public:
    enum MessageType
    {
        TOOL_SELECTION
    };
    MessageFactoryTool();
    Message* produce(int type);
};

#endif // MESSAGEFACTORYTOOL_H
