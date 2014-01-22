#include "messagecreator.h"

MessageCreator::MessageCreator()
{
    this->_messageController = 0L;
}

void MessageCreator::setMessageController(MessageController *messageController)
{
    this->_messageController = messageController;
}

void MessageCreator::sendMessage(QSharedPointer<Message> message)
{
    if (this->_messageController != 0L && message != 0L)
    {
        this->_messageController->send(message);
    }
}
