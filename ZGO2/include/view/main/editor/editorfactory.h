#ifndef EDITORFACTORY_H
#define EDITORFACTORY_H
/**
 * 用于生成相应的编辑器。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "factoryabstract.h"

class EditorFactory : public FactoryAbstract
{
public:
    void* produce(int type);
};

#endif // EDITORFACTORY_H
