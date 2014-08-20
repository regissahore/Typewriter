#include "Messager.h"

Messager::Messager()
{
}

Messager::~Messager()
{
    MessageController::instance()->release(this);
}

void Messager::send(QSharedPointer<Message> message)
{
    if (!message.isNull())
    {
        MessageController::instance()->send(message);
    }
}

void Messager::listen(int messageType)
{
    MessageController::instance()->listen(messageType, this);
}

void Messager::messageEvent(QSharedPointer<Message> message)
{
    Q_UNUSED(message);
}
