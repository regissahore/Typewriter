#ifndef TOOLGOMARKOVOPERATOR_H
#define TOOLGOMARKOVOPERATOR_H
#include "toolgooperator.h"

class ToolGOMarkovOperator : public ToolGOOperator
{
public:
    ToolGOMarkovOperator(SceneGO *sceneGO);
    void activate(QGraphicsSceneMouseEvent *event);
    void setType(const int type);
};

#endif // TOOLGOMARKOVOPERATOR_H
