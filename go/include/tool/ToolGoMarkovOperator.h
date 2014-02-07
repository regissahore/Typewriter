#ifndef TOOLGOMARKOVOPERATOR_H
#define TOOLGOMARKOVOPERATOR_H
#include "ToolGoOperator.h"

class ToolGoMarkovOperator : public ToolGoOperator
{
public:
    ToolGoMarkovOperator(SceneGo *sceneGo);
    void activate(QGraphicsSceneMouseEvent *event);
    void setType(const int type);
};

#endif // TOOLGOMARKOVOPERATOR_H
