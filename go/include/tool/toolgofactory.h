#ifndef TOOLGOFACTORY_H
#define TOOLGOFACTORY_H
#include "DefinationToolType.h"
#include "ToolGoAbstract.h"

class ToolGoFactory
{
public:
    static ToolGoAbstract* produce(SceneGo *sceneGo, const int type);
};

#endif // TOOLGOFACTORY_H
