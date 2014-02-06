#include "MessageController.h"
#include "MessageCreator.h"
#include "MessageListener.h"
using namespace std;

MessageController::MessageController()
{
    this->_messages = new QMap<int, int>();
    this->_listeners = new QVector< QVector<MessageListener*> >();
}

MessageController::~MessageController()
{
    this->_messages->clear();
    for(int i = 0; i < this->_listeners->size(); ++i)
    {
        (*this->_listeners)[i].clear();
    }
    this->_listeners->clear();
}

void MessageController::send(shared_ptr<Message> message)
{
    QMap<int, int>::iterator it = this->_messages->find(message->type());
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

void MessageController::listen(int messageType, MessageListener *listener)
{
    if (this->_messages->find(messageType) == this->_messages->end())
    {
        (*this->_messages)[messageType] = this->_listeners->size();
        this->_listeners->push_back(QVector<MessageListener*>());
    }
    listener->addListenedMessage(messageType);
    int index = (*this->_messages)[messageType];
    (*this->_listeners)[index].push_back(listener);
    listener->setMessageController(this);
}

void MessageController::release(int messageType, MessageListener *listener)
{
    QMap<int, int>::iterator it = this->_messages->find(messageType);
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

