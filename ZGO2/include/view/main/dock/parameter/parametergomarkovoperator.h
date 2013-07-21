#ifndef PARAMETERGOMARKOVOPERATOR_H
#define PARAMETERGOMARKOVOPERATOR_H
/**
 * The parameter for GO operator in Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parametergooperator.h"

class QDoubleSpinBox;
class QCheckBox;

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
    int _markov1DualBreakdownPos;
    QCheckBox *_checkBox1DualBreakdown;
    QCheckBox *_checkBox1BreakdownCorrelate;
    QDoubleSpinBox *_spinBox1Status2FrequencyBreakdown;
    QDoubleSpinBox *_spinBox1Status2FrequencyRepair;
    QDoubleSpinBox *_spinBox1Status2RepairTime;
    QCheckBox *_checkBox6BreakdownCorrelate;

    void addTypeParameter();
    void addMarkovParameter();
    void addMarkov1DualBreakdownParameter();
    void addMarkov1BreakdownCorrelateparameter();
    void addMarkov1Status2Parameter();
    void addMarkov6BreakdownCorrelateparameter();

protected slots:
    void setItemFrequencyBreakdown(double value);
    void setItemFrequencyRepair(double value);
    void setItemRepairTime(double value);
    void setItemMarkov1DualBreakdown(bool value);
    void setItemMarkov1BreakdownCorrelate(bool value);
    void setItemMarkov1FrequencyBreakdown2(double value);
    void setItemMarkov1FrequencyRepair2(double value);
    void setItemMarkov1RepairTime2(double value);
    void setItemMarkov6BreakdownCorrelate(bool value);
};

#endif // PARAMETERGOMARKOVOPERATOR_H
