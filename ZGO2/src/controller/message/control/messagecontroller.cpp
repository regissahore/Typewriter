#include "messagecontroller.h"
#include "messagecreator.h"
#include "messagelistener.h"

/**
 * 构造函数。
 */
MessageController::MessageController()
{
    this->_autoID = 0;
    this->_messages = new QMap<QString, int>();
    this->_listeners = new QVector< QVector<MessageListener*> >();
}

/**
 * 析构函数。
 */
MessageController::~MessageController()
{
    this->_messages->clear();
    for(int i = 0; i < this->_listeners->size(); ++i)
    {
        (*this->_listeners)[i].clear();
    }
    this->_listeners->clear();
}

/**
 * 发送消息，函数结束时消息会被释放。
 * @param message 消息内容。
 */
void MessageController::send(Message *message)
{
    message->setId(this->_autoID++);
    QString messageName = message->name();
    QMap<QString, int>::iterator it = this->_messages->find(messageName);
    if (it != this->_messages->end())
    {
        int index = it.value();
        QVector<MessageListener*> listeners = (*this->_listeners)[index];
        for (int i = 0; i < listeners.size(); ++i)
        {
            listeners[i]->messageEvent(message);
        }
    }
}

/**
 * 监听消息。
 * @param messageName 消息名称。
 * @param listener 监听器。
 */
void MessageController::listen(QString messageName, MessageListener *listener)
{
    if (this->_messages->find(messageName) == this->_messages->end())
    {
        (*this->_messages)[messageName] = this->_listeners->size();
        this->_listeners->push_back(QVector<MessageListener*>());
    }
    int index = (*this->_messages)[messageName];
    (*this->_listeners)[index].push_back(listener);
    listener->setMessageController(this);
}

/**
 * 释放消息监听。
 * @param messageName 消息名称。
 * @param listener 监听器。
 */
void MessageController::release(QString messageName, MessageListener *listener)
{
    QMap<QString, int>::iterator it = this->_messages->find(messageName);
    if (it != this->_messages->end())
    {
        int index = it.value();
        QVector<MessageListener*> *listeners = &((*this->_listeners)[index]);
        for (int i = listeners->size() - 1; i >= 0; --i)
        {
            if ((*listeners)[i] == listener)
            {
                (*this->_listeners)[index].remove(i);
            }
        }
    }
}

