#ifndef TOOLGOPOINTER_H
#define TOOLGOPOINTER_H
/**
 * The pointer tool of the GO Graph.
 * The pointer tool is used to selecting single items in the graphics view.
 * When double click
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgoabstract.h"

class ToolGOPointer : public ToolGOAbstract
{
public:
    ToolGOPointer(SceneGO *sceneGO);
};

#endif // TOOLGOPOINTER_H
