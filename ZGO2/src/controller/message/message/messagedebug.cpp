#include "messagedebug.h"

MessageDebug::MessageDebug() : Message()
{
    this->setName("Debug");
}

QString MessageDebug::toString()
{
    return this->debug();
}

QString MessageDebug::debug() const
{
    return this->_debug;
}

void MessageDebug::setDebug(QString debug)
{
    this->_debug = debug;
}
