#ifndef PARAMETERGOMARKOVOPERATOR_H
#define PARAMETERGOMARKOVOPERATOR_H
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
    QCheckBox *_checkBoxBreakdownCorrelate;
    int _markovBreakdownNumPos;
    QSpinBox *_spinBoxBreakdownNum;
    QDoubleSpinBox *_spinBoxStatus1FrequencyBreakdown;
    QDoubleSpinBox *_spinBoxStatus1FrequencyRepair;
    QDoubleSpinBox *_spinBoxStatus1RepairTime;
    QDoubleSpinBox *_spinBoxStatus2FrequencyBreakdown;
    QDoubleSpinBox *_spinBoxStatus2FrequencyRepair;
    QDoubleSpinBox *_spinBoxStatus2RepairTime;
    QDoubleSpinBox *_spinBoxStatus3FrequencyBreakdown;
    QDoubleSpinBox *_spinBoxStatus3FrequencyRepair;
    QDoubleSpinBox *_spinBoxStatus3RepairTime;
    QDoubleSpinBox *_spinBoxStatus4FrequencyBreakdown;
    QDoubleSpinBox *_spinBoxStatus4FrequencyRepair;
    QDoubleSpinBox *_spinBoxStatus4RepairTime;
    QDoubleSpinBox *_spinBox9FeedbackFrequencyBreakdown;
    QDoubleSpinBox *_spinBox9FeedbackFrequencyRepair;
    QDoubleSpinBox *_spinBox9FeedbackRepairTime;

    void addTypeParameter();
    void addOperatorParameter();
    void addMarkovBreakdownCorrelateParameter();
    void addMarkovBreakdownNumParameter();
    void addMarkovStatus1Parameter();
    void addMarkovStatus2Parameter();
    void addMarkovStatus3Parameter();
    void addMarkovStatus4Parameter();
    void addMarkov9FeedbackParameter();
    void addMarkov11KParameter();
    void addMarkov11IParameter();
    void addMarkov11LParameter();
    void addMarkov11JParameter();
    void addMarkov12AUseDeltaParameter();
    void addMarkov12ADeltaParameter();
    void addMarkov13RelationParameter();
    void addMarkov18LambdaB1Parameter();
    void addMarkov18ABackupParameter();
    void addMarkov19DeltaNumParameter();
    void addMarkov19DeltaParameter();
    void addMarkov22Markov2Parameter();
    void addMarkov23AlphaParameter();
    void addMarkovShowOutput1Parameter();
    void addMarkovShowOutput2Parameter();

protected slots:
    void setItemMarkovGlobalFeedback(bool value);
    void setItemMarkovShowParameter(bool value);
    void setItemMarkovBreakdownCorrelate(bool value);
    void setItemMarkovBreakdownNum(int value);
    void setItemMarkovFrequencyBreakdown1(double value);
    void setItemMarkovFrequencyRepair1();
    void setItemMarkovRepairTime1();
    void setItemMarkovFrequencyBreakdown2(double value);
    void setItemMarkovFrequencyRepair2();
    void setItemMarkovRepairTime2();
    void setItemMarkovFrequencyBreakdown3(double value);
    void setItemMarkovFrequencyRepair3();
    void setItemMarkovRepairTime3();
    void setItemMarkovFrequencyBreakdown4(double value);
    void setItemMarkovFrequencyRepair4();
    void setItemMarkovRepairTime4();
    void setItemMarkov9FeedbackFrequencyBreakdown(double value);
    void setItemMarkov9FeedbackFrequencyRepair();
    void setItemMarkov9FeedbackRepairTime();
    void setItemMarkov11K(int value);
    void setItemMarkov11I(int value);
    void setItemMarkov11L(int value);
    void setItemMarkov11J(int value);
    void setItemMarkov12AUseDelta(bool value);
    void setItemMarkov12ADelta();
    void setItemMarkov13Relation();
    void setItemMarkov18LambdaB1(double value);
    void setItemMarkov18ABackup(double value);
    void setItemMarkov19DeltaNum(int value);
    void setItemMarkov19Delta();
    void setItemMarkov22Markov2();
    void setItemMarkov23Alpha();
    void setItemMarkovShowOutput1(bool value);
    void setItemMarkovShowOutput2(bool value);
};

#endif // PARAMETERGOMARKOVOPERATOR_H
