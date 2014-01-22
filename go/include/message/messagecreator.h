#ifndef MESSAGECREATOR_H
#define MESSAGECREATOR_H
#include "Message.h"
#include "MessageController.h"

class MessageCreator
{
public:
    MessageCreator();
    void setMessageController(MessageController *messageController);
    void sendMessage(QSharedPointer<Message> message);

protected:
    MessageController *_messageController;
};

#endif // MESSAGECREATOR_H
