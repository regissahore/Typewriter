#include "messagelistener.h"

MessageListener::MessageListener()
{
    this->_messageListened = new QVector<int>();
    this->_messageController = 0L;
}

MessageListener::~MessageListener()
{
    this->releaseListener();
}

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

void MessageListener::setMessageController(MessageController *messageController)
{
    this->_messageController = messageController;
}

void MessageListener::addListenedMessage(int messageType)
{
    this->_messageListened->push_back(messageType);
}

void MessageListener::messageEvent(QSharedPointer<Message> message)
{
    Q_UNUSED(message);
}
