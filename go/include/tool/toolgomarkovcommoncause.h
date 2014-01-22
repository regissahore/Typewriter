#ifndef TOOLGOMARKOVCOMMONCAUSE_H
#define TOOLGOMARKOVCOMMONCAUSE_H
#include "ToolGoSelect.h"

class ToolGoMarkovCommonCause : public ToolGoSelect
{
public:
    ToolGoMarkovCommonCause(SceneGo *sceneGo);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

protected:
    void addCommonCause();
};

#endif // TOOLGOMARKOVCOMMONCAUSE_H
