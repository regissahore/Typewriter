#ifndef DIALOGGOMARKOVCUT_H
#define DIALOGGOMARKOVCUT_H

#include <QDialog>

namespace Ui {
class DialogGoMarkovCut;
}

class DialogGoMarkovCut : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGoMarkovCut(QWidget *parent = 0);
    ~DialogGoMarkovCut();
    double interval() const;
    int count() const;
    int order() const;

private slots:
    void on_buttonConfirm_clicked();
    void on_buttonCancel_clicked();

private:
    Ui::DialogGoMarkovCut *ui;
};

#endif // DIALOGGOMARKOVCUT_H
