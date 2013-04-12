#include "gosignalfactory.h"
#include "gosignal.h"

int GOSignalFactory::_autoID = 0;

/**
 * Produce a GOSignal with auto increment ID.
 * @return Pointer to GOOperator.
 */
GOSignal* GOSignalFactory::produce()
{
    GOSignal *signal = new GOSignal();
    signal->setId(GOSignalFactory::_autoID++);
    return signal;
}

/**
 * Set the start value of the auto increment ID.
 * @return id Start value.
 */
void GOSignalFactory::setID(const int id)
{
    GOSignalFactory::_autoID = id;
}

/**
 * Get current ID.
 * @return Current ID.
 */
int GOSignalFactory::currentID()
{
    return GOSignalFactory::_autoID;
}
