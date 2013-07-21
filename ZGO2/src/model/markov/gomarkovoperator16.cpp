#include <qmath.h>
#include "gomarkovoperator16.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator16::GOMarkovOperator16() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(1);
    this->output()->setNumber(2);
}

GOMarkovOperator16::~GOMarkovOperator16()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator16::calcOutputMarkovStatus(double time)
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

void GOMarkovOperator16::calcCommonOutputMarkovStatus(QVector<double> PR)
{
    if (this->isBreakdownCorrelate())
    {
        this->calcCommonOutputMarkovStatusCorrelate(PR);
    }
    else
    {
        this->calcCommonOutputMarkovStatusNormal(PR);
    }
}

double GOMarkovOperator16::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    double PS1 = input[0];
    double PS2 = subInput[0];
    if (this->isBreakdownCorrelate())
    {
        if (index == 1)
        {
            return this->calcTempOutputMarkovStatusCorrelate1(PS1, PS2);
        }
        return this->calcTempOutputMarkovStatusCorrelate2(PS1, PS2);
    }
    if (index == 1)
    {
        return this->calcTempOutputMarkovStatusNormal1(PS1, PS2);
    }
    return this->calcTempOutputMarkovStatusNormal2(PS1, PS2);
}

void GOMarkovOperator16::calcOutputMarkovStatusNormal()
{
    GOMarkovStatus* status1 = this->getPrevMarkovStatus();
    GOMarkovStatus* status2 = this->getPrevSubMarkovStatus();
    double PS1 = status1->probabilityNormal();
    double PS2 = status2->probabilityNormal();
    double PC = this->markovStatus()->probabilityNormal();
    double PR1 = PS1 * PC;
    double PR2 = PS1 * PS2 * PC;
    double QR1 = 1.0 - PR1;
    double QR2 = 1.0 - PR2;
    double lambdaS1 = status1->frequencyBreakdown();
    double lambdaS2 = status2->frequencyBreakdown();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double lambdaR1 = lambdaS1 + lambdaC;
    double muR1 = lambdaR1 * PR1 / QR1;
    double lambdaR2 = lambdaS1 + lambdaS2 + lambdaC;
    double muR2 = lambdaR2 * PR2 / QR2;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR1);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR1);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR1);
    this->markovOutputStatus()->at(1)->setProbabilityNormal(PR2);
    this->markovOutputStatus()->at(1)->setFrequencyBreakdown(lambdaR2);
    this->markovOutputStatus()->at(1)->setFrequencyRepair(muR2);
}

void GOMarkovOperator16::calcCommonOutputMarkovStatusNormal(QVector<double> PR)
{
    GOMarkovStatus* status1 = this->getPrevMarkovStatus();
    GOMarkovStatus* status2 = this->getPrevSubMarkovStatus();
    double PR1 = PR[0];
    double PR2 = PR[1];
    double QR1 = 1.0 - PR1;
    double QR2 = 1.0 - PR2;
    double lambdaS1 = status1->frequencyBreakdown();
    double lambdaS2 = status2->frequencyBreakdown();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double lambdaR1 = lambdaS1 + lambdaC;
    double muR1 = lambdaR1 * PR1 / QR1;
    double lambdaR2 = lambdaS1 + lambdaS2 + lambdaC;
    double muR2 = lambdaR2 * PR2 / QR2;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR1);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR1);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR1);
    this->markovOutputStatus()->at(1)->setProbabilityNormal(PR2);
    this->markovOutputStatus()->at(1)->setFrequencyBreakdown(lambdaR2);
    this->markovOutputStatus()->at(1)->setFrequencyRepair(muR2);
}

double GOMarkovOperator16::calcTempOutputMarkovStatusNormal1(double PS1, double PS2)
{
    Q_UNUSED(PS2);
    double PC = this->markovStatus()->probabilityNormal();
    double PR1 = PS1 * PC;
    return 1 - PR1;
}

double GOMarkovOperator16::calcTempOutputMarkovStatusNormal2(double PS1, double PS2)
{
    double PC = this->markovStatus()->probabilityNormal();
    double PR2 = PS1 * PS2 * PC;
    return 1.0 - PR2;
}

void GOMarkovOperator16::calcOutputMarkovStatusCorrelate()
{

}

void GOMarkovOperator16::calcCommonOutputMarkovStatusCorrelate(QVector<double> PR)
{

}

double GOMarkovOperator16::calcTempOutputMarkovStatusCorrelate1(double PS1, double PS2)
{

}

double GOMarkovOperator16::calcTempOutputMarkovStatusCorrelate2(double PS1, double PS2)
{

}
