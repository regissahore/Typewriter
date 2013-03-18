#ifndef TOOLBOXFACTORY_H
#define TOOLBOXFACTORY_H
/**
 * 工具栏工厂类。
 * @author ZHG <CyberZHG@gmaill.com>
 */
#include "definationtoolboxtype.h"
#include "factoryabstract.h"
#include "toolboxabstract.h"
#include "toolboxnull.h"
#include "toolboxgo.h"

class ToolboxFactory : FactoryAbstract
{
public:
    ToolboxFactory();
    void* produce(int type);
};

#endif // TOOLBOXFACTORY_H
