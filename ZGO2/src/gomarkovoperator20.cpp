#include <qmath.h>
#include "gomarkovoperator20.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator20::GOMarkovOperator20() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(1);
    this->output()->setNumber(1);
}

GOMarkovOperator20::~GOMarkovOperator20()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator20::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GOMarkovStatus *status1 = this->getPrevMarkovStatus();
    GOMarkovStatus *status2 = this->getPrevSubMarkovStatus();
    DoubleVector PS1 = status1->probabilityNormal();
    DoubleVector PS2 = status2->probabilityNormal();
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector PR = PS1 - PS2;
    if (PR < 0.0)
    {
        PR = 0.0;
    }
    DoubleVector QR = 1.0 - PR;
    DoubleVector lambdaR = lambdaS1 + lambdaS2;
    DoubleVector muR = lambdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator20::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    GOMarkovStatus *status1 = this->getPrevMarkovStatus();
    GOMarkovStatus *status2 = this->getPrevSubMarkovStatus();
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector QR = 1.0 - PR[0];
    DoubleVector lambdaR = lambdaS1 + lambdaS2;
    DoubleVector muR = lambdaR * PR[0] / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GOMarkovOperator20::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(index);
    DoubleVector PS1 = input[0];
    DoubleVector PS2 = subInput[0];
    DoubleVector PR = PS1 - PS2;
    if (PR < 0.0)
    {
        PR = 0.0;
    }
    return PR;
}
