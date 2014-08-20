#include <qmath.h>
#include "GoMarkovOperator15b.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator15B::GoMarkovOperator15B() : GoMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator15B::~GoMarkovOperator15B()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator15B::calcQualitativeProbability()
{
    this->_qualitativeOutput[0].setLength(this->input()->number());
    for (int i = 0; i < this->input()->number(); ++i)
    {
        DoubleVector IS = this->getPrevQualitativeStatus(i);
        this->_qualitativeOutput[0].setValue(i, IS.getValue(0));
        this->_qualitativeOutput[0].addHead(i, this->id(), i);
    }
}

void GoMarkovOperator15B::calcOutputMarkovStatus(double time)
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

DoubleVector GoMarkovOperator15B::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
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
