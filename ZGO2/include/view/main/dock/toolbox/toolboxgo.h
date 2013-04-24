#ifndef TOOLBOXGO_H
#define TOOLBOXGO_H
/**
 * GO法的工具栏。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QScrollBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include "toolboxabstract.h"
#include "definationtooltype.h"

class ToolboxGO : public ToolboxAbstract
{
    Q_OBJECT
public:
    explicit ToolboxGO(QWidget *parent = 0);
    void bindMessage(MessageController *controller);
    void messageEvent(Message *message);

protected:
    QVBoxLayout *_layout;

protected:
    QPushButton *_buttonGOPointer;
    QPushButton *_buttonSelect;
    QPushButton *_buttonGOText;
    QPushButton *_buttonGOOperator1;
    QPushButton *_buttonGOOperator2;
    QPushButton *_buttonGOOperator3;
    QPushButton *_buttonGOOperator4;
    QPushButton *_buttonGOOperator5;
    QPushButton *_buttonGOOperator6;
    QPushButton *_buttonGOOperator7;
    QPushButton *_buttonGOOperator8;
    QPushButton *_buttonGOOperator9;
    QPushButton *_buttonGOOperator10;
    QPushButton *_buttonGOOperator11;
    QPushButton *_buttonGOOperator12;
    QPushButton *_buttonGOOperator13;
    QPushButton *_buttonGOOperator14;
    QPushButton *_buttonGOOperator15;
    QPushButton *_buttonGOOperator16;
    QPushButton *_buttonGOOperator17;

protected slots:
    virtual void setToolGOPointer();
    void setToolSelect();
    void setToolGOText();
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

#endif // TOOLBOXGO_H
