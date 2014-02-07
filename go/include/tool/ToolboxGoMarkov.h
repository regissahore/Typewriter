#ifndef TOOLBOXGOMARKOV_H
#define TOOLBOXGOMARKOV_H
#include <QSharedPointer>
#include <QWidget>
#include "ToolboxAbstract.h"

class QPushButton;

namespace Ui {
class ToolboxGoMarkov;
}

class ToolboxGoMarkov : public ToolboxAbstract
{
    Q_OBJECT
    
public:
    explicit ToolboxGoMarkov(QWidget *parent = 0);
    virtual ~ToolboxGoMarkov();
    void bindMessage(MessageController *controller);
    void messageEvent(QSharedPointer<Message> message);
    
private slots:
    void on_buttonPointer_clicked();
    void on_buttonSelect_clicked();
    void on_buttonText_clicked();
    void on_buttonEquivalent_clicked();
    void on_buttonCommonCause_clicked();
    void on_buttonOperator1_clicked();
    void on_buttonOperator2_clicked();
    void on_buttonOperator5_clicked();
    void on_buttonOperator6_clicked();
    void on_buttonOperator9A1_clicked();
    void on_buttonOperator9A2_clicked();
    void on_buttonOperator9B1_clicked();
    void on_buttonOperator9B2_clicked();
    void on_buttonOperator10_clicked();
    void on_buttonOperator11A_clicked();
    void on_buttonOperator12A_clicked();
    void on_buttonOperator13A_clicked();
    void on_buttonOperator13B_clicked();
    void on_buttonOperator15A_clicked();
    void on_buttonOperator15B_clicked();
    void on_buttonOperator16_clicked();
    void on_buttonOperator17_clicked();
    void on_buttonOperator18_clicked();
    void on_buttonOperator18A_clicked();
    void on_buttonOperator19_clicked();
    void on_buttonOperator20_clicked();
    void on_buttonOperator21_clicked();
    void on_buttonOperator22A_clicked();
    void on_buttonOperator22B_clicked();
    void on_buttonOperator23_clicked();
    void on_buttonOperatorSplit_clicked();

private:
    Ui::ToolboxGoMarkov *ui;
};

#endif // TOOLBOXGOMARKOV_H
