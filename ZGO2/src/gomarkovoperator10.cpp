#include <qmath.h>
#include "gomarkovoperator10.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator10::GOMarkovOperator10() : GOMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->setBreakdownCorrelate(false);
}

GOMarkovOperator10::~GOMarkovOperator10()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator10::calcOutputMarkovStatus(double time)
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

void GOMarkovOperator10::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
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

DoubleVector GOMarkovOperator10::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
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

void GOMarkovOperator10::calcOutputMarkovStatusNormal()
{
    DoubleVector PR = 1.0;
    DoubleVector lambdaR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
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

void GOMarkovOperator10::calcCommonOutputMarkovStatusNormal(DoubleVector PR)
{
    DoubleVector lambdaR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector lambdaSi = prevStatus->frequencyBreakdown();
        lambdaR += lambdaSi;
    }
    DoubleVector QR = 1.0 - PR;
    DoubleVector muR = lambdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GOMarkovOperator10::calcTempOutputMarkovStatusNormal(QVector<DoubleVector> input)
{
    DoubleVector PR = 1.0;
    for (int i = 0; i < input.size(); ++i)
    {
        PR *= input[i];
    }
    return PR;
}

void GOMarkovOperator10::calcOutputMarkovStatusCorrelate()
{
    DoubleVector lambdaR = 0.0;
    DoubleVector lmSum = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
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

void GOMarkovOperator10::calcCommonOutputMarkovStatusCorrelate(DoubleVector PR)
{
    DoubleVector lambdaR = 0.0;
    DoubleVector lmSum = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
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

DoubleVector GOMarkovOperator10::calcTempOutputMarkovStatusCorrelate(QVector<DoubleVector> input)
{
    Q_UNUSED(input);
    DoubleVector lambdaR = 0.0;
    DoubleVector lmSum = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector lambdaSi = prevStatus->frequencyBreakdown();
        DoubleVector muSi = prevStatus->frequencyRepair();
        lambdaR += lambdaSi;
        lmSum += lambdaSi / muSi;
    }
    DoubleVector muR = lambdaR / lmSum;
    return 1.0 / (1.0 + lambdaR / muR);
}
