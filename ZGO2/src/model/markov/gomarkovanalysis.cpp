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
#include "gomarkovoperator1e1.h"
#include "gomarkovoperator9a.h"

GOMarkovAnalysis::GOMarkovAnalysis() : GOAnalysis()
{
}

void GOMarkovAnalysis::calcAccumulativeProbability(GOOperator *op, double time)
{
    switch (op->TypedItem::type())
    {
    case GOMarkovOperatorFactory::Operator_Type_9_A1:
        GOMarkovAnalysis::calcAccumulativeProbability_9A1((GOMarkovOperator9A*)op, time);
        break;
    case GOMarkovOperatorFactory::Operator_Type_9_A2:
        GOMarkovAnalysis::calcAccumulativeProbability_9A2((GOMarkovOperator9A*)op, time);
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
    case GOMarkovOperatorFactory::Operator_Type_1_E1:
        this->updateOutputMarkov_1_E1(op);
        break;
    case GOMarkovOperatorFactory::Operator_Type_13_A:
        this->updateOutputMarkov_13_A(op);
        break;
    case GOMarkovOperatorFactory::Operator_Type_13_B:
        this->updateOutputMarkov_13_B(op);
        break;
    case GOMarkovOperatorFactory::Operator_Type_15_A:
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
    GOSignal* signal = op->input()->signal()->at(0);
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
    op->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

void GOMarkovAnalysis::updateOutputMarkov_13_A(GOMarkovOperator *op)
{
    Q_UNUSED(op);
}

void GOMarkovAnalysis::updateOutputMarkov_13_B(GOMarkovOperator *op)
{
    Q_UNUSED(op);
}

void GOMarkovAnalysis::updateOutputMarkov_15_A(GOMarkovOperator *op)
{
    Q_UNUSED(op);
}
