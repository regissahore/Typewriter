#ifndef PARAMETERGOMARKOVCOMMONCAUSE_H
#define PARAMETERGOMARKOVCOMMONCAUSE_H
#include "parameterabstract.h"

class QDoubleSpinBox;

class ParameterGOMarkovCommonCause : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGOMarkovCommonCause(QWidget *parent = 0);
    void bindItem(void *item);

protected:
    QDoubleSpinBox *_spinBoxTotal;
    QDoubleSpinBox *_spinBoxIndividual;
    QDoubleSpinBox *_spinBoxCommon;
    QDoubleSpinBox *_spinBoxBelta;
    QDoubleSpinBox *_spinBoxGammaC;

protected slots:
    void setItemBreakdownTotal(double value);
    void setItemBreakdownIndividual(double value);
    void setItemBreakdownCommon(double value);
    void setItemBelta(double value);
    void setItemGammaC(double value);
};

#endif // PARAMETERGOMARKOVCOMMONCAUSE_H
