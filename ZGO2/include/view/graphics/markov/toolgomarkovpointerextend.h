#ifndef TOOLGOMARKOVPOINTEREXTEND_H
#define TOOLGOMARKOVPOINTEREXTEND_H
/**
 * The extended pointer tool for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgopointerextend.h"

class ToolGOMarkovPointerExtend : public ToolGOPointerExtend
{
public:
    ToolGOMarkovPointerExtend(SceneGO *sceneGO);

protected:
    bool mousePressStatusNullItem(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // TOOLGOMARKOVPOINTEREXTEND_H
