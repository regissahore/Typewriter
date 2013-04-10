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

protected:
    QVBoxLayout *_layout;

private:
    QPushButton *buttonGOPointer;
    QPushButton *buttonSelect;
    QPushButton *buttonGOText;
    QPushButton *buttonGOOperator1;
    QPushButton *buttonGOOperator2;
    QPushButton *buttonGOOperator3;
    QPushButton *buttonGOOperator4;
    QPushButton *buttonGOOperator5;
    QPushButton *buttonGOOperator6;
    QPushButton *buttonGOOperator7;
    QPushButton *buttonGOOperator8;
    QPushButton *buttonGOOperator9;
    QPushButton *buttonGOOperator10;
    QPushButton *buttonGOOperator11;
    QPushButton *buttonGOOperator12;
    QPushButton *buttonGOOperator13;
    QPushButton *buttonGOOperator14;
    QPushButton *buttonGOOperator15;
    QPushButton *buttonGOOperator16;
    QPushButton *buttonGOOperator17;

protected slots:
    void setToolGOPointer();
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
