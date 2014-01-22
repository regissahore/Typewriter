#include "Messager.h"

Messager::Messager() : MessageCreator(), MessageListener()
{
}

Messager::~Messager()
{
    this->MessageListener::~MessageListener();
}

void Messager::bindMessage(MessageController *controller)
{
    this->MessageCreator::setMessageController(controller);
    this->MessageListener::setMessageController(controller);
}
