#ifndef PARAMETERFACTORY_H
#define PARAMETERFACTORY_H
#include "parameterabstract.h"

class ParameterFactory
{
public:
    static ParameterAbstract* produce(int type);
};

#endif // PARAMETERFACTORY_H
