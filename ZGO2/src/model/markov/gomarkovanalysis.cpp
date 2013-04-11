#include "gomarkovanalysis.h"
#include "gooperator.h"
#include "gosignal.h"
#include "goinput.h"
#include "gooutput.h"
#include "gomarkovoperator.h"
#include "gomarkovstatus.h"
#include "goaccumulative.h"

GOMarkovAnalysis::GOMarkovAnalysis() : GOAnalysis()
{
}

void GOMarkovAnalysis::calcAccumulativeProbability(GOOperator *op)
{
    this->GOAnalysis::calcAccumulativeProbability(op);
    this->updateOuputMarkov((GOMarkovOperator*)op);
}

void GOMarkovAnalysis::calcAccumulativeProbability(GOOperator *op, QVector<GOOperator *> commonOperator, QVector<int> commonIndex)
{
    this->GOAnalysis::calcAccumulativeProbability(op, commonOperator, commonIndex);
    this->updateOuputMarkov((GOMarkovOperator*)op);
}

void GOMarkovAnalysis::updateOuputMarkov(GOMarkovOperator *op)
{
    op->markovOutputStatus()->clear();
    BigDecimal breakdown = op->markovStatus()->frequencyBreakdown();
    for (int i = 0; i < op->input()->number(); ++i)
    {
        GOSignal *signal = op->input()->signal()->at(i);
        GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        breakdown = breakdown + prev->markovOutputStatus()->at(prevIndex)->frequencyBreakdown();
    }
    for (int i = 0; i < op->subInput()->number(); ++i)
    {
        GOSignal *signal = op->subInput()->signal()->at(i);
        GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        breakdown = breakdown + prev->markovOutputStatus()->at(prevIndex)->frequencyBreakdown();
    }
    for (int i = 0; i < op->output()->number(); ++i)
    {
        GOMarkovStatus *status = new GOMarkovStatus();
        BigDecimal probability1 = op->accmulatives()->at(i)->accumulative(1) - op->accmulatives()->at(i)->accumulative(0);
        BigDecimal probability2 = op->accmulatives()->at(i)->accumulative(2) - op->accmulatives()->at(i)->accumulative(1);
        status->setFrequencyBreakdown(breakdown);
        status->setFrequencyRepair(breakdown * probability1 / probability2);
        op->markovOutputStatus()->push_back(status);
    }
}
