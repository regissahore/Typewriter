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

DoubleVector GOMarkovOperator6::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(index);
    if (this->isBreakdownCorrelate())
    {
        return this->calcTempOutputMarkovStatusCorrelate(input[0], subInput[0]);
    }
    return this->calcTempOutputMarkovStatusNormal(input[0], subInput[0]);
}

void GOMarkovOperator6::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
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

void GOMarkovOperator6::calcOutputMarkovStatusNormal()
{
    GOMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GOMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
    DoubleVector PS1 = prevStatus1->probabilityNormal();
    DoubleVector PS2 = prevStatus2->probabilityNormal();
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector PR = PS1 * PS2 * PC;
    DoubleVector QR = 1 - PR;
    DoubleVector lambdaS1 = prevStatus1->frequencyBreakdown();
    DoubleVector lambdaS2 = prevStatus2->frequencyBreakdown();
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector lambdaR = lambdaS1 + lambdaS2 + lambdaC;
    DoubleVector muR = lambdaR * PR / QR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator6::calcCommonOutputMarkovStatusNormal(DoubleVector PR)
{
    DoubleVector QR = 1.0 - PR;
    GOMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GOMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
    DoubleVector lambdaS1 = prevStatus1->frequencyBreakdown();
    DoubleVector lambdaS2 = prevStatus2->frequencyBreakdown();
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector lambdaR = lambdaS1 + lambdaS2 + lambdaC;
    DoubleVector muR = lambdaR * PR / QR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GOMarkovOperator6::calcTempOutputMarkovStatusNormal(DoubleVector PS1, DoubleVector PS2)
{
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    return PS1 * PS2 * PC;
}

void GOMarkovOperator6::calcOutputMarkovStatusCorrelate()
{
    GOMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GOMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
    DoubleVector PS1 = prevStatus1->probabilityNormal();
    DoubleVector QS1 = 1.0 - PS1;
    DoubleVector PS2 = prevStatus2->probabilityNormal();
    DoubleVector QS2 = 1.0 - PS2;
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector QC = 1.0 - PC;
    DoubleVector G1 = PS1 * PS2 * PC;
    DoubleVector G2 = QS1 * PS2 * PC + QS2 * PS1 * PC + QC * PS1 * PS2;
    DoubleVector PR = G1 / (G1 + G2);
    DoubleVector lambdaS1 = prevStatus1->frequencyBreakdown();
    DoubleVector lambdaS2 = prevStatus2->frequencyBreakdown();
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector lambdaR = lambdaS1 + lambdaS2 + lambdaC;
    DoubleVector muS1 = prevStatus1->frequencyRepair();
    DoubleVector muS2 = prevStatus2->frequencyRepair();
    DoubleVector muC = this->markovStatus()->frequencyRepair();
    DoubleVector muR = lambdaR / (lambdaS1 / muS1 + lambdaS2 / muS2 + lambdaC / muC);
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator6::calcCommonOutputMarkovStatusCorrelate(DoubleVector PR)
{
    GOMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GOMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
    DoubleVector lambdaS1 = prevStatus1->frequencyBreakdown();
    DoubleVector lambdaS2 = prevStatus2->frequencyBreakdown();
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector lambdaR = lambdaS1 + lambdaS2 + lambdaC;
    DoubleVector muS1 = prevStatus1->frequencyRepair();
    DoubleVector muS2 = prevStatus2->frequencyRepair();
    DoubleVector muC = this->markovStatus()->frequencyRepair();
    DoubleVector muR = lambdaR / (lambdaS1 / muS1 + lambdaS2 / muS2 + lambdaC / muC);
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GOMarkovOperator6::calcTempOutputMarkovStatusCorrelate(DoubleVector PS1, DoubleVector PS2)
{
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    return PS1 * PS2 * PC;
}
