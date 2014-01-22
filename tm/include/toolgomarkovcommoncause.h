#ifndef TOOLGOMARKOVCOMMONCAUSE_H
#define TOOLGOMARKOVCOMMONCAUSE_H
#include "toolgoselect.h"

class ToolGOMarkovCommonCause : public ToolGOSelect
{
public:
    ToolGOMarkovCommonCause(SceneGO *sceneGO);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

protected:
    void addCommonCause();
};

#endif // TOOLGOMARKOVCOMMONCAUSE_H
