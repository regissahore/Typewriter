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
#include "messagefactorytool.h"

class ToolboxGO : public ToolboxAbstract
{
    Q_OBJECT
public:
    explicit ToolboxGO(QWidget *parent = 0);
    void bindMessage(MessageController *controller);

private:
    QPushButton *buttonPointer;
    QPushButton *buttonMove;
    QPushButton *buttonSelect;
    QPushButton *buttonZoom;
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
    QPushButton *buttonGOSignal;

private slots:
    void setToolPointer();
    void setToolMove();
    void setToolSelect();
    void setToolZoom();
    void setToolGOText();
    void setToolGOOperator1();
    void setToolGOOperator2();
    void setToolGOOperator3();
    void setToolGOOperator4();
    void setToolGOOperator5();
    void setToolGOOperator6();
    void setToolGOOperator7();
    void setToolGOOperator8();
    void setToolGOOperator9();
    void setToolGOOperator10();
    void setToolGOOperator11();
    void setToolGOOperator12();
    void setToolGOOperator13();
    void setToolGOOperator14();
    void setToolGOOperator15();
    void setToolGOOperator16();
    void setToolGOOperator17();
    void setToolGOSignal();
};

#endif // TOOLBOXGO_H
