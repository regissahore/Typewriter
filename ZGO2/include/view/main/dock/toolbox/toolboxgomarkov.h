#ifndef TOOLBOXGOMARKOV_H
#define TOOLBOXGOMARKOV_H
/**
 * The toolbox for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolboxgo.h"

class ToolboxGOMarkov : public ToolboxGO
{
    Q_OBJECT
public:
    explicit ToolboxGOMarkov(QWidget *parent = 0);

private:
    QPushButton *buttonGOEquivalent;

protected slots:
    void setToolGOPointer();
    void setToolGOEquivalent();
    virtual void setToolGOOperator1();
    virtual void setToolGOOperator2();
    virtual void setToolGOOperator3();
    virtual void setToolGOOperator4();
    virtual void setToolGOOperator5();
    virtual void setToolGOOperator6();
    virtual void setToolGOOperator7();
    virtual void setToolGOOperator8();
    virtual void setToolGOOperator9();
    virtual void setToolGOOperator10();
    virtual void setToolGOOperator11();
    virtual void setToolGOOperator12();
    virtual void setToolGOOperator13();
    virtual void setToolGOOperator14();
    virtual void setToolGOOperator15();
    virtual void setToolGOOperator16();
    virtual void setToolGOOperator17();
};

#endif // TOOLBOXGOMARKOV_H
