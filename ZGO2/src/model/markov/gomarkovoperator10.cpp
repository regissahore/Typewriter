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

void GOMarkovOperator10::calcCommonOutputMarkovStatus(double PR)
{
    Q_UNUSED(time);
    if (this->isBreakdownCorrelate())
    {
        this->calcCommonOutputMarkovStatusCorrelate(PR);
    }
    else
    {
        this->calcCommonOutputMarkovStatusNormal(PR);
    }
}

double GOMarkovOperator10::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    if (this->isBreakdownCorrelate())
    {
        return this->calcTempOutputMarkovStatusCorrelate(input);
    }
    return this->calcTempOutputMarkovStatusNormal(input);
}

void GOMarkovOperator10::calcOutputMarkovStatusNormal()
{
    double PR = 1.0;
    double lambdaR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        double PSi = prevStatus->probabilityNormal();
        double lambdaSi = prevStatus->frequencyBreakdown();
        PR *= PSi;
        lambdaR += lambdaSi;
    }
    double QR = 1.0 - PR;
    double muR = lambdaR * PR / QR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator10::calcCommonOutputMarkovStatusNormal(double PR)
{
    double lambdaR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        double lambdaSi = prevStatus->frequencyBreakdown();
        lambdaR += lambdaSi;
    }
    double QR = 1.0 - PR;
    double muR = lambdaR * PR / QR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator10::calcTempOutputMarkovStatusNormal(QVector<double> input)
{
    double PR = 1.0;
    for (int i = 0; i < input.size(); ++i)
    {
        PR *= input[i];
    }
    return PR;
}

void GOMarkovOperator10::calcOutputMarkovStatusCorrelate()
{
    double lambdaR = 0.0;
    double lmSum = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        double lambdaSi = prevStatus->frequencyBreakdown();
        double muSi = prevStatus->frequencyRepair();
        lambdaR += lambdaSi;
        lmSum += lambdaSi / muSi;
    }
    double muR = lambdaR / lmSum;
    double PR = 1 / (1 + lambdaR / muR);
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator10::calcCommonOutputMarkovStatusCorrelate(double PR)
{
    double lambdaR = 0.0;
    double lmSum = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        double lambdaSi = prevStatus->frequencyBreakdown();
        double muSi = prevStatus->frequencyRepair();
        lambdaR += lambdaSi;
        lmSum += lambdaSi / muSi;
    }
    double muR = lambdaR / lmSum;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator10::calcTempOutputMarkovStatusCorrelate(QVector<double> input)
{
    Q_UNUSED(input);
    double lambdaR = 0.0;
    double lmSum = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        double lambdaSi = prevStatus->frequencyBreakdown();
        double muSi = prevStatus->frequencyRepair();
        lambdaR += lambdaSi;
        lmSum += lambdaSi / muSi;
    }
    double muR = lambdaR / lmSum;
    return 1 / (1 + lambdaR / muR);
}
