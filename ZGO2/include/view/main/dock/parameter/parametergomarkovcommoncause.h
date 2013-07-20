#ifndef PARAMETERGOMARKOVCOMMONCAUSE_H
#define PARAMETERGOMARKOVCOMMONCAUSE_H
/**
 * The parameter for the common cause in GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parameterabstract.h"

class QDoubleSpinBox;

class ParameterGOMarkovCommonCause : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGOMarkovCommonCause(QWidget *parent = 0);
    void bindItem(void *item);

protected:
    QDoubleSpinBox *_spinBoxCommonCause;

protected slots:
    void setItemCommonCause(double value);
};

#endif // PARAMETERGOMARKOVCOMMONCAUSE_H
