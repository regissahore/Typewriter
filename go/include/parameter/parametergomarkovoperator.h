#ifndef PARAMETERGOMARKOVOPERATOR_H
#define PARAMETERGOMARKOVOPERATOR_H
#include "ParameterGoOperator.h"

class QSpinBox;
class QDoubleSpinBox;
class QCheckBox;

class ParameterGoMarkovOperator : public ParameterGoOperator
{
    Q_OBJECT
public:
    ParameterGoMarkovOperator(QWidget *parent = 0);
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
    int _markovFeedbackNumPos;
    QSpinBox *_spinBoxFeedbackNum;
    QDoubleSpinBox *_spinBoxFeedback1FrequencyBreakdown;
    QDoubleSpinBox *_spinBoxFeedback1FrequencyRepair;
    QDoubleSpinBox *_spinBoxFeedback1RepairTime;
    QDoubleSpinBox *_spinBoxFeedback2FrequencyBreakdown;
    QDoubleSpinBox *_spinBoxFeedback2FrequencyRepair;
    QDoubleSpinBox *_spinBoxFeedback2RepairTime;
    QDoubleSpinBox *_spinBoxFeedback3FrequencyBreakdown;
    QDoubleSpinBox *_spinBoxFeedback3FrequencyRepair;
    QDoubleSpinBox *_spinBoxFeedback3RepairTime;
    QDoubleSpinBox *_spinBoxFeedback4FrequencyBreakdown;
    QDoubleSpinBox *_spinBoxFeedback4FrequencyRepair;
    QDoubleSpinBox *_spinBoxFeedback4RepairTime;

    void addTypeParameter();
    void addOperatorParameter();
    void addMarkovBreakdownCorrelateParameter();
    void addMarkovBreakdownNumParameter();
    void addMarkovStatus1Parameter();
    void addMarkovStatus2Parameter();
    void addMarkovStatus3Parameter();
    void addMarkovStatus4Parameter();
    void addMarkov9FeedbackNumParameter();
    void addMarkov9Feedback1Parameter();
    void addMarkov9Feedback2Parameter();
    void addMarkov9Feedback3Parameter();
    void addMarkov9Feedback4Parameter();
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
    void setItemMarkov9FeedbackNum(int value);
    void setItemMarkov9FrequencyBreakdown1(double value);
    void setItemMarkov9FrequencyRepair1();
    void setItemMarkov9RepairTime1();
    void setItemMarkov9FrequencyBreakdown2(double value);
    void setItemMarkov9FrequencyRepair2();
    void setItemMarkov9RepairTime2();
    void setItemMarkov9FrequencyBreakdown3(double value);
    void setItemMarkov9FrequencyRepair3();
    void setItemMarkov9RepairTime3();
    void setItemMarkov9FrequencyBreakdown4(double value);
    void setItemMarkov9FrequencyRepair4();
    void setItemMarkov9RepairTime4();
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
