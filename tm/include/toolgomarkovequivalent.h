#ifndef TOOLGOMARKOVEQUIVALENT_H
#define TOOLGOMARKOVEQUIVALENT_H
#include "toolgoselect.h"

class ToolGOMarkovEquivalent : public ToolGOSelect
{
public:
    ToolGOMarkovEquivalent(SceneGO *sceneGO);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

protected:
    void addEquivalent();
};

#endif // TOOLGOMARKOVEQUIVALENT_H
