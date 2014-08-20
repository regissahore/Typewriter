#include "Messager.h"
#include "MessageController.h"
using namespace std;

MessageController* MessageController::_instance = nullptr;

MessageController::MessageController()
{
}

MessageController::~MessageController()
{
}

MessageController* MessageController::instance()
{
    if (nullptr == _instance)
    {
        _instance = new MessageController();
    }
    return _instance;
}

void MessageController::send(QSharedPointer<Message> message)
{
    auto listeners = this->_listeners.find(message->type());
    if (listeners != this->_listeners.end())
    {
        for (auto i = listeners.value().begin(); i != listeners.value().end(); ++i)
        {
            (*i)->messageEvent(message);
        }
    }
}

void MessageController::listen(int messageType, Messager *listener)
{
    this->_listeners[messageType].push_back(listener);
}

void MessageController::release(Messager *listener)
{
    for (auto i = this->_listeners.begin(); i != this->_listeners.end(); ++i)
    {
        for (int j = i.value().size() - 1; j >= 0; --j)
        {
            if (i.value()[j] == listener)
            {
                i.value().remove(j);
            }
        }
    }
}
