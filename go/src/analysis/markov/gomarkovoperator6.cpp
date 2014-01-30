#include <qmath.h>
#include "GoMarkovOperator6.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator6::GoMarkovOperator6() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(1);
    this->output()->setNumber(1);
    this->setBreakdownCorrelate(false);
}

GoMarkovOperator6::~GoMarkovOperator6()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator6::calcOutputMarkovStatus(double time)
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

DoubleVector GoMarkovOperator6::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(index);
    if (this->isBreakdownCorrelate())
    {
        return this->calcTempOutputMarkovStatusCorrelate(input[0], subInput[0]);
    }
    return this->calcTempOutputMarkovStatusNormal(input[0], subInput[0]);
}

void GoMarkovOperator6::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
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

void GoMarkovOperator6::calcOutputMarkovStatusNormal()
{
    GoMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GoMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
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

void GoMarkovOperator6::calcCommonOutputMarkovStatusNormal(DoubleVector PR)
{
    DoubleVector QR = 1.0 - PR;
    GoMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GoMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
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

DoubleVector GoMarkovOperator6::calcTempOutputMarkovStatusNormal(DoubleVector PS1, DoubleVector PS2)
{
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    return PS1 * PS2 * PC;
}

void GoMarkovOperator6::calcOutputMarkovStatusCorrelate()
{
    GoMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GoMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
    DoubleVector PS1 = prevStatus1->probabilityNormal();
    DoubleVector QS1 = 1.0 - PS1;
    DoubleVector PS2 = prevStatus2->probabilityNormal();
    DoubleVector QS2 = 1.0 - PS2;
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector QC = 1.0 - PC;
    DoubleVector G1 = PS1 * PS2 * PC;
    DoubleVector G2 = QS1 * PS2 * PC + QS2 * PS1 * PC + QC * PS1 * PS2;
    DoubleVector PR = G1 / (G1 + G2);
    DoubleVector QR = 1.0 - PR;
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

void GoMarkovOperator6::calcCommonOutputMarkovStatusCorrelate(DoubleVector PR)
{
    GoMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GoMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
    DoubleVector lambdaS1 = prevStatus1->frequencyBreakdown();
    DoubleVector lambdaS2 = prevStatus2->frequencyBreakdown();
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector lambdaR = lambdaS1 + lambdaS2 + lambdaC;
    DoubleVector QR = 1.0 - PR;
    DoubleVector muR = lambdaR * PR / QR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GoMarkovOperator6::calcTempOutputMarkovStatusCorrelate(DoubleVector PS1, DoubleVector PS2)
{
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    return PS1 * PS2 * PC;
}
