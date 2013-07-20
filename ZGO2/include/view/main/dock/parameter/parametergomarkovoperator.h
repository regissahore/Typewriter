#ifndef PARAMETERGOMARKOVOPERATOR_H
#define PARAMETERGOMARKOVOPERATOR_H
/**
 * The parameter for GO operator in Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parametergooperator.h"

class QDoubleSpinBox;

class ParameterGOMarkovOperator : public ParameterGOOperator
{
    Q_OBJECT
public:
    ParameterGOMarkovOperator(QWidget *parent = 0);
    void bindItem(void *item);

protected:
    QDoubleSpinBox *_spinBoxFrequencyBreakdown;
    QDoubleSpinBox *_spinBoxFrequencyRepair;
    QDoubleSpinBox *_spinBoxRepairTime;

    void addTypeParameter();
    void addMarkovParameter();

protected slots:
    void setItemFrequencyBreakdown(double value);
    void setItemFrequencyRepair(double value);
    void setItemRepairTime(double value);
};

#endif // PARAMETERGOMARKOVOPERATOR_H
