#include <qmath.h>
#include "GoMarkovOperator10.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator10::GoMarkovOperator10() : GoMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->setBreakdownCorrelate(false);
}

GoMarkovOperator10::~GoMarkovOperator10()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator10::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    if (this->isBreakdownCorrelate())
    {
        this->calcOutputMarkovStatusCorrelate();
    }
    else
    {
        this->calcOutputMarkovStatusNormal();
    }
}

void GoMarkovOperator10::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    if (this->isBreakdownCorrelate())
    {
        this->calcCommonOutputMarkovStatusCorrelate(PR[0]);
    }
    else
    {
        this->calcCommonOutputMarkovStatusNormal(PR[0]);
    }
}

DoubleVector GoMarkovOperator10::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    if (this->isBreakdownCorrelate())
    {
        return this->calcTempOutputMarkovStatusCorrelate(input);
    }
    return this->calcTempOutputMarkovStatusNormal(input);
}

void GoMarkovOperator10::calcOutputMarkovStatusNormal()
{
    DoubleVector PR = 1.0;
    DoubleVector lambdaR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector PSi = prevStatus->probabilityNormal();
        DoubleVector lambdaSi = prevStatus->frequencyBreakdown();
        PR *= PSi;
        lambdaR += lambdaSi;
    }
    DoubleVector QR = 1.0 - PR;
    DoubleVector muR = lambdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GoMarkovOperator10::calcCommonOutputMarkovStatusNormal(DoubleVector PR)
{
    DoubleVector lambdaR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector lambdaSi = prevStatus->frequencyBreakdown();
        lambdaR += lambdaSi;
    }
    DoubleVector QR = 1.0 - PR;
    DoubleVector muR = lambdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GoMarkovOperator10::calcTempOutputMarkovStatusNormal(QVector<DoubleVector> input)
{
    DoubleVector PR = 1.0;
    for (int i = 0; i < input.size(); ++i)
    {
        PR *= input[i];
    }
    return PR;
}

void GoMarkovOperator10::calcOutputMarkovStatusCorrelate()
{
    DoubleVector lambdaR = 0.0;
    DoubleVector lmSum = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector lambdaSi = prevStatus->frequencyBreakdown();
        DoubleVector muSi = prevStatus->frequencyRepair();
        lambdaR += lambdaSi;
        lmSum += lambdaSi / muSi;
    }
    DoubleVector muR = lambdaR / lmSum;
    DoubleVector PR = 1 / (1 + lambdaR / muR);
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GoMarkovOperator10::calcCommonOutputMarkovStatusCorrelate(DoubleVector PR)
{
    DoubleVector lambdaR = 0.0;
    DoubleVector lmSum = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector lambdaSi = prevStatus->frequencyBreakdown();
        DoubleVector muSi = prevStatus->frequencyRepair();
        lambdaR += lambdaSi;
        lmSum += lambdaSi / muSi;
    }
    DoubleVector muR = lambdaR / lmSum;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GoMarkovOperator10::calcTempOutputMarkovStatusCorrelate(QVector<DoubleVector> input)
{
    Q_UNUSED(input);
    DoubleVector lambdaR = 0.0;
    DoubleVector lmSum = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector lambdaSi = prevStatus->frequencyBreakdown();
        DoubleVector muSi = prevStatus->frequencyRepair();
        lambdaR += lambdaSi;
        lmSum += lambdaSi / muSi;
    }
    DoubleVector muR = lambdaR / lmSum;
    return 1.0 / (1.0 + lambdaR / muR);
}
