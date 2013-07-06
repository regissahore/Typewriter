#ifndef DIALOGMATRIXINPUT_H
#define DIALOGMATRIXINPUT_H

#include <QDialog>

namespace Ui {
class DialogMatrixInput;
}

class DialogMatrixInput : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogMatrixInput(QWidget *parent = 0);
    ~DialogMatrixInput();
    
protected:
    Ui::DialogMatrixInput *ui;
};

#endif // DIALOGMATRIXINPUT_H
