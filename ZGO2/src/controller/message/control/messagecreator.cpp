#include "messagecreator.h"

/**
 * 构造函数。
 */
MessageCreator::MessageCreator()
{
    this->_messageController = 0L;
}

/**
 * 设置消息控制器。
 * @param messageController 消息控制器。
 */
void MessageCreator::setMessageController(MessageController *messageController)
{
    this->_messageController = messageController;
}

/**
 * 发送消息。
 * @param message 消息。
 */
void MessageCreator::sendMessage(Message *message)
{
    if (this->_messageController != 0L && message != 0L)
    {
        this->_messageController->send(message);
    }
}
