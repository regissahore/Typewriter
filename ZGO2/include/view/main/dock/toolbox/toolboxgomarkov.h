#ifndef TOOLBOXGOMARKOV_H
#define TOOLBOXGOMARKOV_H

#include <QWidget>
#include "toolboxabstract.h"

class QPushButton;

namespace Ui {
class ToolboxGOMarkov;
}

class ToolboxGOMarkov : public ToolboxAbstract
{
    Q_OBJECT
    
public:
    explicit ToolboxGOMarkov(QWidget *parent = 0);
    virtual ~ToolboxGOMarkov();
    void bindMessage(MessageController *controller);
    void messageEvent(Message *message);
    
private slots:
    void on_buttonPointer_clicked();
    void on_buttonSelect_clicked();
    void on_buttonText_clicked();
    void on_buttonEquivalent_clicked();
    void on_pushButton_clicked();
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
    Ui::ToolboxGOMarkov *ui;
};

#endif // TOOLBOXGOMARKOV_H
