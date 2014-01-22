#include "gosignalfactory.h"
#include "gosignal.h"

int GOSignalFactory::_autoID = 0;

GOSignal* GOSignalFactory::produce()
{
    GOSignal *signal = new GOSignal();
    signal->setId(GOSignalFactory::_autoID++);
    return signal;
}

void GOSignalFactory::setID(const int id)
{
    GOSignalFactory::_autoID = id;
}

int GOSignalFactory::currentID()
{
    return GOSignalFactory::_autoID;
}
