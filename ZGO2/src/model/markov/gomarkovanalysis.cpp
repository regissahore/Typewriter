#include <QVector>
#include <qmath.h>
#include "gomarkovanalysis.h"
#include "gooperator.h"
#include "gosignal.h"
#include "goinput.h"
#include "gooutput.h"
#include "gomarkovoperator.h"
#include "gomarkovstatus.h"
#include "goaccumulative.h"
#include "gomarkovoperatorfactory.h"
#include "gomarkovoperator9a.h"
#include "gomarkovoperator13.h"

GOMarkovAnalysis::GOMarkovAnalysis() : GOAnalysis()
{
}

void GOMarkovAnalysis::calcAccumulativeProbability(GOOperator *op, double time)
{
    switch (op->TypedItem::type())
    {
    case GOMarkovOperatorFactory::Operator_Type_9A1:
        GOMarkovAnalysis::calcAccumulativeProbability_9A1((GOMarkovOperator9A*)op, time);
        break;
    case GOMarkovOperatorFactory::Operator_Type_9A2:
        GOMarkovAnalysis::calcAccumulativeProbability_9A2((GOMarkovOperator9A*)op, time);
        break;
    case GOMarkovOperatorFactory::Operator_Type_13A:
        GOMarkovAnalysis::calcAccumulativeProbability_13A((GOMarkovOperator13*)op);
        this->updateOutputMarkov((GOMarkovOperator*)op);
        break;
    case GOMarkovOperatorFactory::Operator_Type_13B:
        GOMarkovAnalysis::calcAccumulativeProbability_13B((GOMarkovOperator13*)op);
        this->updateOutputMarkov((GOMarkovOperator*)op);
        break;
    case GOMarkovOperatorFactory::Operator_Type_15A:
        GOMarkovAnalysis::calcAccumulativeProbability_15A((GOMarkovOperator*)op);
        this->updateOutputMarkov((GOMarkovOperator*)op);
        break;
    default:
        this->GOAnalysis::calcAccumulativeProbability(op);
        this->updateOutputMarkov((GOMarkovOperator*)op);
    }
}

void GOMarkovAnalysis::calcAccumulativeProbability(GOOperator *op, QVector<GOOperator *> commonOperator, QVector<int> commonIndex, double time)
{
    Q_UNUSED(time);
    this->GOAnalysis::calcAccumulativeProbability(op, commonOperator, commonIndex);
    this->updateOutputMarkov((GOMarkovOperator*)op);
}

void GOMarkovAnalysis::calcAccumulativeProbability_9A1(GOMarkovOperator9A *op, double time)
{
    GOSignal* signal = op->input()->signal()->at(0);
    GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
    int prevIndex = prev->output()->getSignalIndex(signal);
    GOMarkovStatus *prevStatus = prev->markovOutputStatus()->at(prevIndex);
    double lamda1 = prevStatus->frequencyBreakdown();
    double miu1 = prevStatus->frequencyRepair();
    double lamdaC = op->markovStatus()->frequencyBreakdown();
    double miuC = op->markovStatus()->frequencyRepair();
    double lamdaF = op->markovFeedbackStatus()->frequencyBreakdown();
    double miuF = op->markovFeedbackStatus()->frequencyRepair();
    double lamda2 = lamdaC + lamdaF;
    double miu2 = (lamda2 * miuC * miuF) / (lamdaC * miuF + lamdaF * miuC);
    double s1 = 0.5 * (-(lamda1 + lamda2 + miu1 + miu2) + sqrt((lamda1 - lamda2 + miu1 - miu2) * (lamda1 - lamda2 + miu1 - miu2) + 4 * lamda1 * lamda2));
    double s2 = 0.5 * (-(lamda1 + lamda2 + miu1 + miu2) - sqrt((lamda1 - lamda2 + miu1 - miu2) * (lamda1 - lamda2 + miu1 - miu2) + 4 * lamda1 * lamda2));
    double pr1 = miu1 * miu2 / s1 / s2 + (s1 * s1 + (miu1 + miu2) * s1 + miu1 * miu2) / (s1 * (s1 - s2)) * exp(s1 * time) + (s2 * s2 + (miu1 + miu2) * s2 + miu1 * miu2) / (s2 * (s2 - s1)) * exp(s2 * time);
    double pr2 = 1 - pr1;
    op->accmulatives()->clear();
    op->accmulatives()->push_back(new GOAccumulative());
    op->accmulatives()->at(0)->setNumber(3);
    op->accmulatives()->at(0)->setAccumulative(0, 0.0);
    op->accmulatives()->at(0)->setAccumulative(1, pr1);
    op->accmulatives()->at(0)->setAccumulative(2, 1.0);
    op->markovOutputStatus()->clear();
    op->markovOutputStatus()->push_back(new GOMarkovStatus());
    op->markovOutputStatus()->at(0)->setProbabilityNormal(pr1);
    double lamdaR = lamda1 + lamda2 + lamdaC;
    double miuR = lamdaR * pr1 / pr2;
    op->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    op->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

void GOMarkovAnalysis::calcAccumulativeProbability_9A2(GOMarkovOperator9A *op, double time)
{
    GOSignal* signal = op->input()->signal()->at(0);
    GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
    int prevIndex = prev->output()->getSignalIndex(signal);
    GOMarkovStatus *prevStatus = prev->markovOutputStatus()->at(prevIndex);
    double lamda1 = prevStatus->frequencyBreakdown();
    double miu1 = prevStatus->frequencyRepair();
    double lamdaC = op->markovStatus()->frequencyBreakdown();
    double miuC = op->markovStatus()->frequencyRepair();
    double lamdaF = op->markovFeedbackStatus()->frequencyBreakdown();
    double miuF = op->markovFeedbackStatus()->frequencyRepair();
    double lamdaE = lamdaC + lamdaF;
    double miuE = (lamdaE * miuC * miuF) / (lamdaC * miuF + lamdaF * miuC + lamdaC * lamdaF);
    double pr1 = (miu1 * miuE + lamdaE * miu1 * exp(-(miuE + lamdaE) * time) + lamda1 * miuE * exp(-(miu1 + lamda1) * time) + lamda1 * lamdaE * exp(-(miu1 + lamda1 + miuE + lamdaE) * time)) / ((miu1 + lamda1) * (miuE + lamdaE));
    double pr2 = 1 - pr1;
    op->accmulatives()->clear();
    op->accmulatives()->push_back(new GOAccumulative());
    op->accmulatives()->at(0)->setNumber(3);
    op->accmulatives()->at(0)->setAccumulative(0, 0.0);
    op->accmulatives()->at(0)->setAccumulative(1, pr1);
    op->accmulatives()->at(0)->setAccumulative(2, 1.0);
    op->markovOutputStatus()->clear();
    op->markovOutputStatus()->push_back(new GOMarkovStatus());
    op->markovOutputStatus()->at(0)->setProbabilityNormal(pr1);
    double lamdaR = lamda1 + lamdaF + lamdaC;
    double miuR = lamdaR * pr1 / pr2;
    op->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    op->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

void GOMarkovAnalysis::calcAccumulativeProbability_13A(GOMarkovOperator13 *op)
{
    QVector<QVector<double> > *relation = op->relation();
    QVector<double> pS1;
    QVector<double> lamdaS;
    for (int i = 0; i < op->input()->number(); ++i)
    {
        GOSignal* signal = op->input()->signal()->at(i);
        GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        GOAccumulative *accumulative = prev->accmulatives()->at(prevIndex);
        GOMarkovStatus *prevStatus = prev->markovOutputStatus()->at(prevIndex);
        pS1.push_back(accumulative->probability(1));
        lamdaS.push_back(prevStatus->frequencyBreakdown());
    }
    op->accmulatives()->clear();
    op->markovOutputStatus()->clear();
    for (int j = 0; j < op->output()->number(); ++j)
    {
        double pr1 = 1.0;
        double lamdaR = 0.0;
        for (int i = 0; i < op->input()->number(); ++i)
        {
            pr1 *= relation->at(i).at(j) * pS1[i];
            lamdaR += relation->at(i).at(j) * lamdaS[i];
        }
        double pr2 = 1 - pr1;
        double miuR = lamdaR * pr1 / pr2;
        op->accmulatives()->push_back(new GOAccumulative());
        op->accmulatives()->at(j)->setNumber(3);
        op->accmulatives()->at(j)->setAccumulative(0, 0.0);
        op->accmulatives()->at(j)->setAccumulative(1, pr1);
        op->accmulatives()->at(j)->setAccumulative(2, 1.0);
        op->markovOutputStatus()->push_back(new GOMarkovStatus());
        op->markovOutputStatus()->at(j)->setProbabilityNormal(pr1);
        op->markovOutputStatus()->at(j)->setFrequencyBreakdown(lamdaR);
        op->markovOutputStatus()->at(j)->setFrequencyRepair(miuR);
    }
}

void GOMarkovAnalysis::calcAccumulativeProbability_13B(GOMarkovOperator13 *op)
{
    QVector<QVector<double> > *relation = op->relation();
    QVector<double> pS1;
    QVector<double> lamdaS;
    for (int i = 0; i < op->input()->number(); ++i)
    {
        GOSignal* signal = op->input()->signal()->at(i);
        GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        GOAccumulative *accumulative = prev->accmulatives()->at(prevIndex);
        GOMarkovStatus *prevStatus = prev->markovOutputStatus()->at(prevIndex);
        pS1.push_back(accumulative->probability(1));
        lamdaS.push_back(prevStatus->frequencyBreakdown());
    }
    op->accmulatives()->clear();
    op->markovOutputStatus()->clear();
    for (int j = 0; j < op->output()->number(); ++j)
    {
        double pr1 = 1.0;
        double miuR = 0.0;
        for (int i = 0; i < op->input()->number(); ++i)
        {
            pr1 += relation->at(i).at(j) * pS1[i];
            miuR += relation->at(i).at(j) * lamdaS[i];
        }
        double pr2 = 1 - pr1;
        double lamdaR = miuR * pr2 / pr1;
        op->accmulatives()->push_back(new GOAccumulative());
        op->accmulatives()->at(j)->setNumber(3);
        op->accmulatives()->at(j)->setAccumulative(0, 0.0);
        op->accmulatives()->at(j)->setAccumulative(1, pr1);
        op->accmulatives()->at(j)->setAccumulative(2, 1.0);
        op->markovOutputStatus()->push_back(new GOMarkovStatus());
        op->markovOutputStatus()->at(j)->setProbabilityNormal(pr1);
        op->markovOutputStatus()->at(j)->setFrequencyBreakdown(lamdaR);
        op->markovOutputStatus()->at(j)->setFrequencyRepair(miuR);
    }
}

void GOMarkovAnalysis::calcAccumulativeProbability_15A(GOMarkovOperator *op)
{
    double pc = op->markovStatus()->probabilityNormal();
    op->accmulatives()->clear();
    for (int i = 0; i < op->input()->number(); ++i)
    {
        GOSignal* signal = op->input()->signal()->at(i);
        GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        GOAccumulative *accumulative = prev->accmulatives()->at(prevIndex);
        double ps = accumulative->probability(1);
        double pr1 = ps * pc;
        op->accmulatives()->push_back(new GOAccumulative());
        op->accmulatives()->at(i)->setNumber(3);
        op->accmulatives()->at(i)->setAccumulative(0, 0.0);
        op->accmulatives()->at(i)->setAccumulative(1, pr1);
        op->accmulatives()->at(i)->setAccumulative(2, 1.0);
    }
}

void GOMarkovAnalysis::updateOutputMarkov(GOMarkovOperator *op)
{
    op->markovOutputStatus()->clear();
    for (int i = 0; i < op->output()->number(); ++i)
    {
        op->markovOutputStatus()->push_back(new GOMarkovStatus());
        op->markovOutputStatus()->at(i)->setProbabilityNormal(op->accmulatives()->at(i)->probability(1));
    }
    switch (op->TypedItem::type())
    {
    case GOMarkovOperatorFactory::Operator_Type_1:
        this->updateOutputMarkov_1(op);
        break;
    case GOMarkovOperatorFactory::Operator_Type_2:
        this->updateOutputMarkov_2(op);
        break;
    case GOMarkovOperatorFactory::Operator_Type_5:
        this->updateOutputMarkov_5(op);
        break;
    case GOMarkovOperatorFactory::Operator_Type_6:
        this->updateOutputMarkov_6(op);
        break;
    case GOMarkovOperatorFactory::Operator_Type_10:
        this->updateOutputMarkov_10(op);
        break;
    case GOMarkovOperatorFactory::Operator_Type_11:
        this->updateOutputMarkov_11(op);
        break;
    case GOMarkovOperatorFactory::Operator_Type_15A:
        this->updateOutputMarkov_15_A(op);
        break;
    }
}

void GOMarkovAnalysis::updateOutputMarkov_1(GOMarkovOperator *op)
{
    GOSignal* signal = op->input()->signal()->at(0);
    GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
    int prevIndex = prev->output()->getSignalIndex(signal);
    GOMarkovStatus *prevStatus = prev->markovOutputStatus()->at(prevIndex);
    double lamdaS = prevStatus->frequencyBreakdown();
    double lamdaC = op->markovStatus()->frequencyBreakdown();
    double pr1 = op->markovOutputStatus()->at(0)->probabilityNormal();
    double pr2 = 1 - pr1;
    double lamdaR = lamdaS + lamdaC;
    double miuR = lamdaR * pr1 / pr2;
    op->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    op->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

void GOMarkovAnalysis::updateOutputMarkov_2(GOMarkovOperator *op)
{
    double pr1 = op->markovOutputStatus()->at(0)->probabilityNormal();
    double pr2 = 1 - pr1;
    double miuR = 0.0;
    for (int i = 0; i < op->input()->number(); ++i)
    {
        GOSignal *signal = op->input()->signal()->at(i);
        GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        GOMarkovStatus *prevStatus = prev->markovOutputStatus()->at(prevIndex);
        double miuS = prevStatus->frequencyRepair();
        miuR += miuS;
    }
    double lamdaR = miuR * pr2 / pr1;
    op->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    op->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

void GOMarkovAnalysis::updateOutputMarkov_5(GOMarkovOperator *op)
{
    double lamdaR = op->markovStatus()->frequencyBreakdown();
    double miuR = op->markovStatus()->frequencyRepair();
    op->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    op->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

void GOMarkovAnalysis::updateOutputMarkov_6(GOMarkovOperator *op)
{
    GOSignal* signal = op->input()->signal()->at(0);
    GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
    int prevIndex = prev->output()->getSignalIndex(signal);
    GOMarkovStatus *prevStatus = prev->markovOutputStatus()->at(prevIndex);
    double lamdaS1 = prevStatus->frequencyBreakdown();

    signal = op->subInput()->signal()->at(0);
    prev = (GOMarkovOperator*)signal->next(op);
    prevIndex = prev->output()->getSignalIndex(signal);
    prevStatus = prev->markovOutputStatus()->at(prevIndex);
    double lamdaS2 = prevStatus->frequencyBreakdown();

    double lamdaC = op->markovStatus()->frequencyBreakdown();
    double pr1 = op->markovOutputStatus()->at(0)->probabilityNormal();
    double pr2 = 1 - pr1;
    double lamdaR = lamdaS1 + lamdaS2 + lamdaC;
    double miuR = lamdaR * pr1 / pr2;
    op->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    op->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

void GOMarkovAnalysis::updateOutputMarkov_10(GOMarkovOperator *op)
{
    double pr1 = op->markovOutputStatus()->at(0)->probabilityNormal();
    double pr2 = 1 - pr1;
    double lamdaR = 0.0;
    for (int i = 0; i < op->input()->number(); ++i)
    {
        GOSignal *signal = op->input()->signal()->at(i);
        GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        GOMarkovStatus *prevStatus = prev->markovOutputStatus()->at(prevIndex);
        double lamdaS = prevStatus->frequencyBreakdown();
        lamdaR += lamdaS;
    }
    double miuR = lamdaR * pr1 / pr2;
    op->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    op->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

void GOMarkovAnalysis::updateOutputMarkov_11(GOMarkovOperator *op)
{
    Q_UNUSED(op);
}

void GOMarkovAnalysis::updateOutputMarkov_1_E1(GOMarkovOperator *op)
{
    Q_UNUSED(op);
    /*GOSignal* signal = op->input()->signal()->at(0);
    GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
    int prevIndex = prev->output()->getSignalIndex(signal);
    GOMarkovStatus *prevStatus = prev->markovOutputStatus()->at(prevIndex);
    double lamdaS = prevStatus->frequencyBreakdown();
    double lamdaC1 = op->markovStatus()->frequencyBreakdown();
    double lamdaC2 = ((GOMarkovOperator1E1*)op)->markovStatus2()->frequencyBreakdown();
    double pr1 = op->markovOutputStatus()->at(0)->probabilityNormal();
    double pr2 = 1 - pr1;
    double lamdaR = lamdaS + lamdaC1 + lamdaC2;
    double miuR = lamdaR * pr1 / pr2;
    op->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    op->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);*/
}

void GOMarkovAnalysis::updateOutputMarkov_15_A(GOMarkovOperator *op)
{
    double lamdaC = op->markovStatus()->frequencyBreakdown();
    op->markovOutputStatus()->clear();
    for (int i = 0; i < op->input()->number(); ++i)
    {
        GOSignal* signal = op->input()->signal()->at(i);
        GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        GOMarkovStatus *prevStatus = prev->markovOutputStatus()->at(prevIndex);
        double pr1 = op->accmulatives()->at(i)->probability(1);
        double pr2 = 1 - pr1;
        double lamdaS = prevStatus->frequencyBreakdown();
        double lamdaR = lamdaS + lamdaC;
        double miuR = lamdaR * pr1 / pr2;
        op->markovOutputStatus()->push_back(new GOMarkovStatus());
        op->markovOutputStatus()->at(i)->setProbabilityNormal(pr1);
        op->markovOutputStatus()->at(i)->setFrequencyBreakdown(lamdaR);
        op->markovOutputStatus()->at(i)->setFrequencyRepair(miuR);
    }
}
