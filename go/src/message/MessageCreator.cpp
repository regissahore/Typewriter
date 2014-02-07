#include "MessageCreator.h"
using namespace std;

MessageCreator::MessageCreator()
{
    this->_messageController = nullptr;
}

void MessageCreator::setMessageController(MessageController *messageController)
{
    this->_messageController = messageController;
}

void MessageCreator::sendMessage(shared_ptr<Message> message)
{
    if (this->_messageController != nullptr && message != nullptr)
    {
        this->_messageController->send(message);
    }
}
