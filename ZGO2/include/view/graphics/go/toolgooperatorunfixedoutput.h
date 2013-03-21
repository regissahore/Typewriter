#ifndef TOOLGOOPERATORUNFIXEDOUTPUT_H
#define TOOLGOOPERATORUNFIXEDOUTPUT_H
/**
 * The GO Operator tool which has unfixed number of output.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgooperator.h"
#include "dialogintegerinput.h"

class ToolGOOperatorUnfixedOutput : public ToolGOOperator
{
public:
    ToolGOOperatorUnfixedOutput(SceneGO *sceneGO);
    void getOutputNumber();
    void activate();
};

#endif // TOOLGOOPERATORUNFIXEDOUTPUT_H
