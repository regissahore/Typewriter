#include <qmath.h>
#include "gomarkovoperator6.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator6::GOMarkovOperator6() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(1);
    this->output()->setNumber(1);
    this->setBreakdownCorrelate(false);
}

GOMarkovOperator6::~GOMarkovOperator6()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator6::calcOutputMarkovStatus(double time)
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

double GOMarkovOperator6::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput)
{
    Q_UNUSED(time);
    if (this->isBreakdownCorrelate())
    {
        return this->calcTempOutputMarkovStatusCorrelate(input[0], subInput[0]);
    }
    return this->calcTempOutputMarkovStatusNormal(input[0], subInput[0]);
}

void GOMarkovOperator6::calcCommonOutputMarkovStatus(double PR)
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

void GOMarkovOperator6::calcOutputMarkovStatusNormal()
{
    GOMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GOMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
    double PS1 = prevStatus1->probabilityNormal();
    double PS2 = prevStatus2->probabilityNormal();
    double PC = this->markovStatus()->probabilityNormal();
    double PR = PS1 * PS2 * PC;
    double QR = 1 - PR;
    double lambdaS1 = prevStatus1->frequencyBreakdown();
    double lambdaS2 = prevStatus2->frequencyBreakdown();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double lambdaR = lambdaS1 + lambdaS2 + lambdaC;
    double muR = lambdaR * PR / QR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator6::calcCommonOutputMarkovStatusNormal(double PR)
{
    double QR = 1.0 - PR;
    GOMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GOMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
    double lambdaS1 = prevStatus1->frequencyBreakdown();
    double lambdaS2 = prevStatus2->frequencyBreakdown();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double lambdaR = lambdaS1 + lambdaS2 + lambdaC;
    double muR = lambdaR * PR / QR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator6::calcTempOutputMarkovStatusNormal(double PS1, double PS2)
{
    double PC = this->markovStatus()->probabilityNormal();
    return PS1 * PS2 * PC;
}

void GOMarkovOperator6::calcOutputMarkovStatusCorrelate()
{
    GOMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GOMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
    double PS1 = prevStatus1->probabilityNormal();
    double QS1 = 1.0 - PS1;
    double PS2 = prevStatus2->probabilityNormal();
    double QS2 = 1.0 - PS2;
    double PC = this->markovStatus()->probabilityNormal();
    double QC = 1.0 - PC;
    double G1 = PS1 * PS2 * PC;
    double G2 = QS1 * PS2 * PC + QS2 * PS1 * PC + QC * PS1 * PS2;
    double PR = G1 / (G1 + G2);
    double lambdaS1 = prevStatus1->frequencyBreakdown();
    double lambdaS2 = prevStatus2->frequencyBreakdown();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double lambdaR = lambdaS1 + lambdaS2 + lambdaC;
    double muS1 = prevStatus1->frequencyRepair();
    double muS2 = prevStatus2->frequencyRepair();
    double muC = this->markovStatus()->frequencyRepair();
    double muR = lambdaR / (lambdaS1 / muS1 + lambdaS2 / muS2 + lambdaC / muC);
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator6::calcCommonOutputMarkovStatusCorrelate(double PR)
{
    GOMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GOMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
    double lambdaS1 = prevStatus1->frequencyBreakdown();
    double lambdaS2 = prevStatus2->frequencyBreakdown();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double lambdaR = lambdaS1 + lambdaS2 + lambdaC;
    double muS1 = prevStatus1->frequencyRepair();
    double muS2 = prevStatus2->frequencyRepair();
    double muC = this->markovStatus()->frequencyRepair();
    double muR = lambdaR / (lambdaS1 / muS1 + lambdaS2 / muS2 + lambdaC / muC);
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator6::calcTempOutputMarkovStatusCorrelate(double PS1, double PS2)
{
    double PC = this->markovStatus()->probabilityNormal();
    return PS1 * PS2 * PC;
}
