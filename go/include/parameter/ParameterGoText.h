#ifndef PARAMETERGOTEXT_H
#define PARAMETERGOTEXT_H
#include "ParameterAbstract.h"

class QLineEdit;

class ParameterGoText : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGoText(QWidget *parent = 0);
    void bindItem(void *item);

protected:
    QLineEdit *_lineEditText;
    void addTextParameter();

protected slots:
    void setItemText(QString value);
};

#endif // PARAMETERGOTEXT_H
