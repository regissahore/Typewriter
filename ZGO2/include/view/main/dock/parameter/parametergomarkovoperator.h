#ifndef PARAMETERGOMARKOVOPERATOR_H
#define PARAMETERGOMARKOVOPERATOR_H
/**
 * The parameter for GO operator in Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parametergooperator.h"

class QSpinBox;
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
    QCheckBox *_checkBoxBreakdownCorrelate;
    int _markov1DualBreakdownPos;
    QCheckBox *_checkBox1DualBreakdown;
    QDoubleSpinBox *_spinBox1Status2FrequencyBreakdown;
    QDoubleSpinBox *_spinBox1Status2FrequencyRepair;
    QDoubleSpinBox *_spinBox1Status2RepairTime;
    QSpinBox *_spinBoxMarkov11K;

    void addTypeParameter();
    void addMarkovParameter();
    void addMarkovBreakdownCorrelateParameter();
    void addMarkov1DualBreakdownParameter();
    void addMarkov1Status2Parameter();
    void addMarkov11KParameter();
    void addMarkov22Markov2Parameter();
    void addMarkov23AlphaParameter();

protected slots:
    void setItemFrequencyBreakdown(double value);
    void setItemFrequencyRepair(double value);
    void setItemRepairTime(double value);
    void setItemMarkovBreakdownCorrelate(bool value);
    void setItemMarkov1DualBreakdown(bool value);
    void setItemMarkov1FrequencyBreakdown2(double value);
    void setItemMarkov1FrequencyRepair2(double value);
    void setItemMarkov1RepairTime2(double value);
    void setItemMarkov11K(int value);
    void setItemMarkov22Markov2();
    void setItemMarkov23Alpha();
};

#endif // PARAMETERGOMARKOVOPERATOR_H
