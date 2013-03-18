#ifndef EDITORFACTORY_H
#define EDITORFACTORY_H
/**
 * 用于生成相应的编辑器。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QObject>
#include "factoryabstract.h"
#include "definationeditortype.h"
#include "editorwelcome.h"
#include "editorgo.h"

class EditorFactory : public FactoryAbstract
{
public:
    void* produce(qint32 type);
};

#endif // EDITORFACTORY_H
