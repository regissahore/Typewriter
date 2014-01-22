#ifndef TOOLGOZOOM_H
#define TOOLGOZOOM_H
#include "toolgoabstract.h"

class ToolGOZoom : public ToolGOAbstract
{
public:
    ToolGOZoom(SceneGO *sceneGO);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TOOLGOZOOM_H
