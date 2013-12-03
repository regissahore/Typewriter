#include "messagelistener.h"

/**
 * 构造函数。
 */
MessageListener::MessageListener()
{
    this->_messageListened = new QVector<int>();
    this->_messageController = 0L;
}

/**
 * 析构函数。
 */
MessageListener::~MessageListener()
{
    this->releaseListener();
}

/**
 * Release the listener.
 */
void MessageListener::releaseListener()
{
    if (this->_messageController)
    {
        for (int i = 0; i < this->_messageListened->size(); ++i)
        {
            this->_messageController->release((*this->_messageListened)[i], this);
        }
    }
    this->_messageListened->clear();
}

/**
 * 设置消息控制器，不需要主动调用，在设置监听时由控制器调用。
 * @param messageController 消息控制器。
 */
void MessageListener::setMessageController(MessageController *messageController)
{
    this->_messageController = messageController;
}

/**
 * 设置已监听消息，不需要主动调用，在设置监听时由控制器调用。
 * @param message 消息名称。
 */
void MessageListener::addListenedMessage(int messageType)
{
    this->_messageListened->push_back(messageType);
}

/**
 * 在监听事件发生时被调用，一般情况下子类都需要重载这个方法。
 * @param message 消息。
 */
void MessageListener::messageEvent(QSharedPointer<Message> message)
{
    Q_UNUSED(message);
}
