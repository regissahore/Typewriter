#include "GoSignalFactory.h"
#include "GoSignal.h"

int GoSignalFactory::_autoID = 0;

GoSignal* GoSignalFactory::produce()
{
    GoSignal *signal = new GoSignal();
    signal->setId(GoSignalFactory::_autoID++);
    return signal;
}

void GoSignalFactory::setID(const int id)
{
    GoSignalFactory::_autoID = id;
}

int GoSignalFactory::currentID()
{
    return GoSignalFactory::_autoID;
}
