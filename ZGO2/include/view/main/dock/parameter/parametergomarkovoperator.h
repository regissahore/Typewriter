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
    int _markovDualBreakdownPos;
    QCheckBox *_checkBoxDualBreakdown;
    QDoubleSpinBox *_spinBoxStatus1FrequencyBreakdown;
    QDoubleSpinBox *_spinBoxStatus1FrequencyRepair;
    QDoubleSpinBox *_spinBoxStatus1RepairTime;
    QDoubleSpinBox *_spinBoxStatus2FrequencyBreakdown;
    QDoubleSpinBox *_spinBoxStatus2FrequencyRepair;
    QDoubleSpinBox *_spinBoxStatus2RepairTime;
    QDoubleSpinBox *_spinBox9FeedbackFrequencyBreakdown;
    QDoubleSpinBox *_spinBox9FeedbackFrequencyRepair;
    QDoubleSpinBox *_spinBox9FeedbackRepairTime;

    void addTypeParameter();
    void addMarkovParameter();
    void addMarkovBreakdownCorrelateParameter();
    void addMarkovDualBreakdownParameter();
    void addMarkovStatus1Parameter();
    void addMarkovStatus2Parameter();
    void addMarkov9FeedbackParameter();
    void addMarkov11KParameter();
    void addMarkov11IParameter();
    void addMarkov11LParameter();
    void addMarkov11JParameter();
    void addMarkov13RelationParameter();
    void addMarkov18LambdaB1Parameter();
    void addMarkov18ABackupParameter();
    void addMarkov19DeltaNumParameter();
    void addMarkov19DeltaParameter();
    void addMarkov22Markov2Parameter();
    void addMarkov23AlphaParameter();

protected slots:
    void setItemFrequencyBreakdown(double value);
    void setItemFrequencyRepair(double value);
    void setItemRepairTime(double value);
    void setItemMarkovBreakdownCorrelate(bool value);
    void setItemMarkovDualBreakdown(bool value);
    void setItemMarkovFrequencyBreakdown1(double value);
    void setItemMarkovFrequencyRepair1(double value);
    void setItemMarkovRepairTime1(double value);
    void setItemMarkovFrequencyBreakdown2(double value);
    void setItemMarkovFrequencyRepair2(double value);
    void setItemMarkovRepairTime2(double value);
    void setItemMarkov9FeedbackFrequencyBreakdown(double value);
    void setItemMarkov9FeedbackFrequencyRepair(double value);
    void setItemMarkov9FeedbackRepairTime(double value);
    void setItemMarkov11K(int value);
    void setItemMarkov11I(int value);
    void setItemMarkov11L(int value);
    void setItemMarkov11J(int value);
    void setItemMarkov13Relation();
    void setItemMarkov18LambdaB1(double value);
    void setItemMarkov18ABackup(double value);
    void setItemMarkov19DeltaNum(int value);
    void setItemMarkov19Delta();
    void setItemMarkov22Markov2();
    void setItemMarkov23Alpha();
};

#endif // PARAMETERGOMARKOVOPERATOR_H
