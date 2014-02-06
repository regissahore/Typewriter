#include <QObject>
#include "Message.h"

Message::Message()
{
    this->_message = nullptr;
    this->paramInt = 0;
    this->paramString = "";
}

Message::~Message()
{
}

void* Message::message() const
{
    return this->_message;
}

void Message::setMessage(void* message)
{
    this->_message = message;
}

