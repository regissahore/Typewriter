#ifndef TOOLBOXGO_H
#define TOOLBOXGO_H
#include "stable.h"
#include "ToolboxAbstract.h"

class QPushButton;

namespace Ui {
class ToolboxGo;
}

class ToolboxGo : public ToolboxAbstract
{
    Q_OBJECT
    
public:
    explicit ToolboxGo(QWidget *parent = 0);
    virtual ~ToolboxGo();
    void bindMessage();
    void messageEvent(QSharedPointer<Message> message);
    
private slots:
    void on_buttonPointer_clicked();
    void on_buttonSelect_clicked();
    void on_buttonText_clicked();
    void on_buttonOperator1_clicked();
    void on_buttonOperator2_clicked();
    void on_buttonOperator3_clicked();
    void on_buttonOperator5_clicked();
    void on_buttonOperator6_clicked();
    void on_buttonOperator7_clicked();
    void on_buttonOperator9_clicked();
    void on_buttonOperator10_clicked();
    void on_buttonOperator11_clicked();

private:
    Ui::ToolboxGo *ui;
};

#endif // TOOLBOXGO_H
