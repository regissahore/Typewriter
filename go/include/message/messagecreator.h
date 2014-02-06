#ifndef MESSAGECREATOR_H
#define MESSAGECREATOR_H
#include <memory>
#include "Message.h"
#include "MessageController.h"

class MessageCreator
{
public:
    MessageCreator();
    void setMessageController(MessageController *messageController);
    void sendMessage(std::shared_ptr<Message> message);

protected:
    MessageController *_messageController;
};

#endif // MESSAGECREATOR_H
