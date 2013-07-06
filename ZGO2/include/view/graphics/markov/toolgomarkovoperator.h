#ifndef TOOLGOMARKOVOPERATOR_H
#define TOOLGOMARKOVOPERATOR_H
/**
 * The tool for placing operator of GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgooperator.h"

class ToolGOMarkovOperator : public ToolGOOperator
{
public:
    ToolGOMarkovOperator(SceneGO *sceneGO);
    void activate(QGraphicsSceneMouseEvent *event);
    void setType(const int type);
};

#endif // TOOLGOMARKOVOPERATOR_H
