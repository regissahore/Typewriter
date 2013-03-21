#ifndef TOOLGOOPERATORTYPE13_H
#define TOOLGOOPERATORTYPE13_H
/**
 * The type 13 operator of GO graph.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgooperatorunfixedinput.h"
#include "toolgooperatorunfixedoutput.h"
#include "itemgooperatortype13.h"

class ToolGOOperatorType13 : public ToolGOOperatorUnfixedInput
{
public:
    ToolGOOperatorType13(SceneGO *sceneGO);
    void getOutputNumber();
    void activate();
};

#endif // TOOLGOOPERATORTYPE13_H
