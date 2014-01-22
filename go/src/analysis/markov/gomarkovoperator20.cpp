#include <qmath.h>
#include "GoMarkovOperator20.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator20::GoMarkovOperator20() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(1);
    this->output()->setNumber(1);
}

GoMarkovOperator20::~GoMarkovOperator20()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator20::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GoMarkovStatus *status1 = this->getPrevMarkovStatus();
    GoMarkovStatus *status2 = this->getPrevSubMarkovStatus();
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

void GoMarkovOperator20::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    GoMarkovStatus *status1 = this->getPrevMarkovStatus();
    GoMarkovStatus *status2 = this->getPrevSubMarkovStatus();
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector QR = 1.0 - PR[0];
    DoubleVector lambdaR = lambdaS1 + lambdaS2;
    DoubleVector muR = lambdaR * PR[0] / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GoMarkovOperator20::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
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
