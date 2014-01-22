#ifndef TOOLGOMOVE_H
#define TOOLGOMOVE_H
#include "toolgoabstract.h"
#include "itemmoveable.h"

class ToolGOMove : public ToolGOAbstract
{
public:
    ToolGOMove(SceneGO *sceneGO);
protected:
    ItemMoveable *_item;
};

#endif // TOOLGOMOVE_H
