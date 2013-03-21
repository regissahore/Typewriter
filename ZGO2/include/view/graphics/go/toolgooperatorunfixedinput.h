#ifndef TOOLGOOPERATORUNFIXEDINPUT_H
#define TOOLGOOPERATORUNFIXEDINPUT_H
/**
 * The GO Operator tool which has unfixed number of input.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgooperator.h"
#include "dialogintegerinput.h"

class ToolGOOperatorUnfixedInput : public ToolGOOperator
{
public:
    ToolGOOperatorUnfixedInput(SceneGO *sceneGO);
    void getInputNumber();
};

#endif // TOOLGOOPERATORUNFIXEDINPUT_H
