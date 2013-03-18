#ifndef MESSAGEFACTORYEDITOR_H
#define MESSAGEFACTORYEDITOR_H
/**
 * 和编辑器相关的事件。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "typeditem.h"
#include "messagefactory.h"
#include "messageeditortype.h"
#include "messageeditorselection.h"

class MessageFactoryEditor : public MessageFactory
{
public:
    enum MessageType
    {
        EDITOR_TYPE,
        EDITOR_SELECTION
    };

    MessageFactoryEditor();
    Message* produce(int type);
};

#endif // MESSAGEFACTORYEDITOR_H
