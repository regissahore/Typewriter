#ifndef TOOLGOFACTORY_H
#define TOOLGOFACTORY_H
/**
 * The factory of GO tools.
 * The produce method is static, thus the class should not instantiated.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "definationtooltype.h"
#include "toolgoabstract.h"
#include "toolgopointer.h"
#include "toolgomove.h"

class ToolGOFactory
{
public:
    static ToolGOAbstract* produce(SceneGO *sceneGO, int type);
};

#endif // TOOLGOFACTORY_H
