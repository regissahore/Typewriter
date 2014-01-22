#ifndef TOOLGOFACTORY_H
#define TOOLGOFACTORY_H
#include "definationtooltype.h"
#include "toolgoabstract.h"

class ToolGOFactory
{
public:
    static ToolGOAbstract* produce(SceneGO *sceneGO, const int type);
};

#endif // TOOLGOFACTORY_H
