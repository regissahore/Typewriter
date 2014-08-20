#ifndef TOOLGOMARKOVPOINTEREXTEND_H
#define TOOLGOMARKOVPOINTEREXTEND_H
#include "ToolGoPointerExtend.h"

class ToolGoMarkovPointerExtend : public ToolGoPointerExtend
{
public:
    ToolGoMarkovPointerExtend(SceneGo *sceneGo);

protected:
    bool mousePressStatusNullItem(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // TOOLGOMARKOVPOINTEREXTEND_H
