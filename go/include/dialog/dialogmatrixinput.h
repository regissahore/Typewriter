#ifndef DIALOGMATRIXINPUT_H
#define DIALOGMATRIXINPUT_H

#include <QDialog>

namespace Ui {
class DialogMatrixInput;
}

class QTableWidget;

class DialogMatrixInput : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogMatrixInput(QWidget *parent = 0);
    ~DialogMatrixInput();
    QTableWidget* table() const;
    
protected:
    Ui::DialogMatrixInput *ui;
};

#endif // DIALOGMATRIXINPUT_H
