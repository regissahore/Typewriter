#ifndef TOOLGOZOOM_H
#define TOOLGOZOOM_H
#include "ToolGoAbstract.h"

class ToolGoZoom : public ToolGoAbstract
{
public:
    ToolGoZoom(SceneGo *sceneGo);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TOOLGOZOOM_H
