#ifndef TOOLGOMOVE_H
#define TOOLGOMOVE_H
/**
 * The move tool of the GO graph.
 * When drag an item, it will move the item.
 * When drag the scene, it will move the scene.
 */
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
