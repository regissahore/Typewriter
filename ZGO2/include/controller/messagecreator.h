#ifndef MESSAGECREATOR_H
#define MESSAGECREATOR_H
/**
 * 用于产生消息，如果想继承此类请直接引用MessageController.h文件。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "controller/message.h"
#include "controller/messagecontroller.h"

class MessageCreator
{
public:
    MessageCreator();
    void setMessageController(MessageController *messageController);
    void sendMessage(Message *message);

private:
    MessageController *_messageController;
};

#endif // MESSAGECREATOR_H
