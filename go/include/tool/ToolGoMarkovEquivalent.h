#ifndef TOOLGOMARKOVEQUIVALENT_H
#define TOOLGOMARKOVEQUIVALENT_H
#include "ToolGoSelect.h"

class ToolGoMarkovEquivalent : public ToolGoSelect
{
public:
    ToolGoMarkovEquivalent(SceneGo *sceneGo);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

protected:
    void addEquivalent();
};

#endif // TOOLGOMARKOVEQUIVALENT_H
