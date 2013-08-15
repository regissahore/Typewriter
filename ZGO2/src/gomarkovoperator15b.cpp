#include <qmath.h>
#include "gomarkovoperator15b.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator15B::GOMarkovOperator15B() : GOMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator15B::~GOMarkovOperator15B()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator15B::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    this->markovOutputStatus()->at(0)->setVectorLength(this->input()->number());
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector PR = prevStatus->probabilityNormal();
        DoubleVector lambdaR = prevStatus->frequencyBreakdown();
        DoubleVector muR = prevStatus->frequencyRepair();
        this->markovOutputStatus()->at(0)->setProbabilityNormal(i, PR.getValue(0));
        this->markovOutputStatus()->at(0)->setFrequencyBreakdown(i, lambdaR.getValue(0));
        this->markovOutputStatus()->at(0)->setFrequencyRepair(i, muR.getValue(0));
    }
}

DoubleVector GOMarkovOperator15B::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(index);
    Q_UNUSED(subInput);
    DoubleVector PR;
    PR.setLength(input.size());
    for (int i = 0; i < input.size(); ++i)
    {
        PR.setValue(i, input[i].getValue(0));
    }
    return PR;
}
