#ifndef MESSAGEFACTORYEDITOR_H
#define MESSAGEFACTORYEDITOR_H
/**
 * 和编辑器相关的事件。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "model/typeditem.h"
#include "controller/messagefactory.h"
#include "controller/messageeditortype.h"
#include "controller/messageeditorselection.h"

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
