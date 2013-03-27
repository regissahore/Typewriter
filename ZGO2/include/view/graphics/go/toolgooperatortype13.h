#ifndef TOOLGOOPERATORTYPE13_H
#define TOOLGOOPERATORTYPE13_H
/**
 * The type 13 operator of GO graph.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgooperator.h"
#include "itemgooperatortype13.h"

class ToolGOOperatorType13 : public ToolGOOperator
{
public:
    ToolGOOperatorType13(SceneGO *sceneGO);
    void activate();
};

#endif // TOOLGOOPERATORTYPE13_H
