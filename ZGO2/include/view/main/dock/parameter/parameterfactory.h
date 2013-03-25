#ifndef PARAMETERFACTORY_H
#define PARAMETERFACTORY_H
/**
 * A static parameter factory.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parameterabstract.h"

class ParameterFactory
{
public:
    static ParameterAbstract* produce(int type);
};

#endif // PARAMETERFACTORY_H
