#include "factoryabstract.h"

FactoryAbstract::FactoryAbstract()
{
    this->setId(0);
}

void FactoryAbstract::setId(int id)
{
    this->_id = id;
}

int FactoryAbstract::id()
{
    return this->_id++;
}
