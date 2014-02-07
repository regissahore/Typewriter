#ifndef TOOLGOMOVE_H
#define TOOLGOMOVE_H
#include "ToolGoAbstract.h"
#include "ItemMoveable.h"

class ToolGoMove : public ToolGoAbstract
{
public:
    ToolGoMove(SceneGo *sceneGo);
protected:
    ItemMoveable *_item;
};

#endif // TOOLGOMOVE_H
