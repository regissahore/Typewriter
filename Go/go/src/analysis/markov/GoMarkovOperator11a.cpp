#include "GoMarkovOperator11a.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoMarkovStatus.h"

GoMarkovOperator11A::GoMarkovOperator11A()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator11A::~GoMarkovOperator11A()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator11A::calcQualitativeProbability()
{
    this->_qualitativeOutput[0].setLength(this->input()->number());
    for (int i = 0; i < this->input()->number(); ++i)
    {
        DoubleVector IS = this->getPrevQualitativeStatus(i);
        this->_qualitativeOutput[0].setValue(i, IS.getValue(0));
        this->_qualitativeOutput[0].addHead(i, this->id(), i);
    }
}

void GoMarkovOperator11A::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    this->markovOutputStatus()->at(0)->setVectorLength(this->input()->number());
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector PR = prevStatus->probabilityNormal();
        DoubleVector lambdaR = prevStatus->frequencyBreakdown();
        DoubleVector muR = prevStatus->frequencyRepair();
        this->markovOutputStatus()->at(0)->setProbabilityNormal(i, PR.getValue(0));
        this->markovOutputStatus()->at(0)->setFrequencyBreakdown(i, lambdaR.getValue(0));
        this->markovOutputStatus()->at(0)->setFrequencyRepair(i, muR.getValue(0));
        this->markovOutputStatus()->at(0)->addHeadProbabilityNormal(i, this->id(), i);
        this->markovOutputStatus()->at(0)->addHeadFrequencyBreakdown(i, this->id(), i);
        this->markovOutputStatus()->at(0)->addHeadFrequencyRepair(i, this->id(), i);
    }
}

DoubleVector GoMarkovOperator11A::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(index);
    Q_UNUSED(subInput);
    DoubleVector PR;
    PR.setLength(input.size());
    for (int i = 0; i < input.size(); ++i)
    {
        PR.setValue(i, input[i].getValue(0));
        PR.addHead(i, this->id(), i);
    }
    return PR;
}
