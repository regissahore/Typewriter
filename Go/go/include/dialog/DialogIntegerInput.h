#ifndef DIALOGINTEGERINPUT_H
#define DIALOGINTEGERINPUT_H
#include "stable.h"

class DialogIntegerInput : public QDialog
{
    Q_OBJECT
public:
    explicit DialogIntegerInput(QWidget *parent = 0);
    void setText(const QString text);
    QSpinBox* integerInput() const;

private:
    QLabel *_textLabel;
    QSpinBox *_integerInput;
};

#endif // DIALOGINTEGERINPUT_H
