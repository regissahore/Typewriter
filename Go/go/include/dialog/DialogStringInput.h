#ifndef DIALOGSTRINGINPUT_H
#define DIALOGSTRINGINPUT_H
#include "stable.h"

class DialogStringInput : public QDialog
{
    Q_OBJECT
public:
    DialogStringInput(QWidget *parent = 0);
    void setText(const QString text);
    QLineEdit* stringInput() const;

private:
    QLabel *_textLabel;
    QLineEdit *_stringInput;

private slots:
    void confirm();
    void cancel();
};

#endif // DIALOGSTRINGINPUT_H
