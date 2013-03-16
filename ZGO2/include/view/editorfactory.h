#ifndef EDITORFACTORY_H
#define EDITORFACTORY_H
/**
 * 用于生成相应的编辑器。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QObject>
#include "model/factoryabstract.h"
#include "view/editorwelcome.h"
#include "view/editorgo.h"

class EditorFactory : public FactoryAbstract
{
public:
    enum EditorType
    {
        TYPE_WELCOME,   /** 欢迎界面。 */
        TYPE_GO         /** GO法编辑器界面。 */
    };
    void* produce(qint32 type);
};

#endif // EDITORFACTORY_H
