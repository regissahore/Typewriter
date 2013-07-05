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

GOMarkovAnalysis::GOMarkovAnalysis() : GOAnalysis()
{
}

void GOMarkovAnalysis::calcAccumulativeProbability(GOOperator *op)
{
    this->GOAnalysis::calcAccumulativeProbability(op);
    this->updateOutputMarkov((GOMarkovOperator*)op);
}

void GOMarkovAnalysis::calcAccumulativeProbability(GOOperator *op, QVector<GOOperator *> commonOperator, QVector<int> commonIndex)
{
    this->GOAnalysis::calcAccumulativeProbability(op, commonOperator, commonIndex);
    this->updateOutputMarkov((GOMarkovOperator*)op);
}

void GOMarkovAnalysis::updateOutputMarkov(GOMarkovOperator *op)
{
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
    case GOMarkovOperatorFactory::Operator_Type_9_A1:
        this->updateOutputMarkov_9_A1(op);
        break;
    case GOMarkovOperatorFactory::Operator_Type_9_A2:
        this->updateOutputMarkov_9_A2(op);
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

void GOMarkovAnalysis::updateOutputMarkov_9_A1(GOMarkovOperator *op)
{
    Q_UNUSED(op);
}

void GOMarkovAnalysis::updateOutputMarkov_9_A2(GOMarkovOperator *op)
{
    Q_UNUSED(op);
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
