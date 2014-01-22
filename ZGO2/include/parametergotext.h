#ifndef PARAMETERGOTEXT_H
#define PARAMETERGOTEXT_H
#include "parameterabstract.h"

class QLineEdit;

class ParameterGOText : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGOText(QWidget *parent = 0);
    void bindItem(void *item);

protected:
    QLineEdit *_lineEditText;
    void addTextParameter();

protected slots:
    void setItemText(QString value);
};

#endif // PARAMETERGOTEXT_H
