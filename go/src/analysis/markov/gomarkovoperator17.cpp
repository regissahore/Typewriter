#include <qmath.h>
#include "GoMarkovOperator17.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator17::GoMarkovOperator17() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(1);
    this->output()->setNumber(2);
}

GoMarkovOperator17::~GoMarkovOperator17()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator17::calcOutputMarkovStatus(double time)
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

void GoMarkovOperator17::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
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

DoubleVector GoMarkovOperator17::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    DoubleVector PS1 = input[0];
    DoubleVector PS2 = subInput[0];
    if (this->isBreakdownCorrelate())
    {
        if (index == 0)
        {
            return this->calcTempOutputMarkovStatusCorrelate1(PS1, PS2);
        }
        return this->calcTempOutputMarkovStatusCorrelate2(PS1, PS2);
    }
    if (index == 0)
    {
        return this->calcTempOutputMarkovStatusNormal1(PS1, PS2);
    }
    return this->calcTempOutputMarkovStatusNormal2(PS1, PS2);
}

void GoMarkovOperator17::calcOutputMarkovStatusNormal()
{
    GoMarkovStatus* status1 = this->getPrevMarkovStatus();
    GoMarkovStatus* status2 = this->getPrevSubMarkovStatus();
    DoubleVector PS1 = status1->probabilityNormal();
    DoubleVector PS2 = status2->probabilityNormal();
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector PR1 = PC;
    DoubleVector PR2 = PS1 * PS2 * PC;
    DoubleVector QR2 = 1.0 - PR2;
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector muC = this->markovStatus()->frequencyRepair();
    DoubleVector lambdaR1 = lambdaC;
    DoubleVector muR1 = muC;
    DoubleVector lambdaR2 = lambdaS1 + lambdaS2 + lambdaC;
    DoubleVector muR2 = lambdaR2 * PR2 / QR2;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR1);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR1);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR1);
    this->markovOutputStatus()->at(1)->setProbabilityNormal(PR2);
    this->markovOutputStatus()->at(1)->setFrequencyBreakdown(lambdaR2);
    this->markovOutputStatus()->at(1)->setFrequencyRepair(muR2);
}

void GoMarkovOperator17::calcCommonOutputMarkovStatusNormal(QVector<DoubleVector> PR)
{
    GoMarkovStatus* status1 = this->getPrevMarkovStatus();
    GoMarkovStatus* status2 = this->getPrevSubMarkovStatus();
    DoubleVector PR1 = PR[0];
    DoubleVector PR2 = PR[1];
    DoubleVector QR2 = 1.0 - PR2;
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector muC = this->markovStatus()->frequencyRepair();
    DoubleVector lambdaR1 = lambdaC;
    DoubleVector muR1 = muC;
    DoubleVector lambdaR2 = lambdaS1 + lambdaS2 + lambdaC;
    DoubleVector muR2 = lambdaR2 * PR2 / QR2;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR1);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR1);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR1);
    this->markovOutputStatus()->at(1)->setProbabilityNormal(PR2);
    this->markovOutputStatus()->at(1)->setFrequencyBreakdown(lambdaR2);
    this->markovOutputStatus()->at(1)->setFrequencyRepair(muR2);
}

DoubleVector GoMarkovOperator17::calcTempOutputMarkovStatusNormal1(DoubleVector PS1, DoubleVector PS2)
{
    Q_UNUSED(PS1);
    Q_UNUSED(PS2);
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    return PC;
}

DoubleVector GoMarkovOperator17::calcTempOutputMarkovStatusNormal2(DoubleVector PS1, DoubleVector PS2)
{
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    return PS1 * PS2 * PC;
}

void GoMarkovOperator17::calcOutputMarkovStatusCorrelate()
{
    GoMarkovStatus* status1 = this->getPrevMarkovStatus();
    GoMarkovStatus* status2 = this->getPrevSubMarkovStatus();
    DoubleVector PS1 = status1->probabilityNormal();
    DoubleVector PS2 = status2->probabilityNormal();
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector QS1 = 1.0 - PS1;
    DoubleVector QS2 = 1.0 - PS2;
    DoubleVector QC = 1.0 - PC;
    DoubleVector G1 = PC;
    DoubleVector G2 = PS1 * QC;
    DoubleVector G3 = PS1 * PS2 * PC;
    DoubleVector G4 = QS1 * PS2 * PC + QS2 * PS1 * PC + QC * PS1 * PS2;
    DoubleVector PR1 = G1 / (G1 + G2);
    DoubleVector PR2 = G3 / (G3 + G4);
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector muS1 = status1->frequencyRepair();
    DoubleVector muS2 = status2->frequencyRepair();
    DoubleVector muC = this->markovStatus()->frequencyRepair();
    DoubleVector lambdaR1 = lambdaS1 + lambdaC;
    DoubleVector lambdaR2 = lambdaS1 + lambdaS2 + lambdaC;
    DoubleVector muR1 = lambdaR1 / (lambdaS1 / muS1 + lambdaC / muC);
    DoubleVector muR2 = lambdaR2 / (lambdaS1 / muS1 + lambdaS2 / muS2 + lambdaC / muC);
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR1);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR1);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR1);
    this->markovOutputStatus()->at(1)->setProbabilityNormal(PR2);
    this->markovOutputStatus()->at(1)->setFrequencyBreakdown(lambdaR2);
    this->markovOutputStatus()->at(1)->setFrequencyRepair(muR2);
}

void GoMarkovOperator17::calcCommonOutputMarkovStatusCorrelate(QVector<DoubleVector> PR)
{
    GoMarkovStatus* status1 = this->getPrevMarkovStatus();
    GoMarkovStatus* status2 = this->getPrevSubMarkovStatus();
    DoubleVector PR1 = PR[0];
    DoubleVector PR2 = PR[1];
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector muS1 = status1->frequencyRepair();
    DoubleVector muS2 = status2->frequencyRepair();
    DoubleVector muC = this->markovStatus()->frequencyRepair();
    DoubleVector lambdaR1 = lambdaS1 + lambdaC;
    DoubleVector lambdaR2 = lambdaS1 + lambdaS2 + lambdaC;
    DoubleVector muR1 = lambdaR1 / (lambdaS1 / muS1 + lambdaC / muC);
    DoubleVector muR2 = lambdaR2 / (lambdaS1 / muS1 + lambdaS2 / muS2 + lambdaC / muC);
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR1);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR1);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR1);
    this->markovOutputStatus()->at(1)->setProbabilityNormal(PR2);
    this->markovOutputStatus()->at(1)->setFrequencyBreakdown(lambdaR2);
    this->markovOutputStatus()->at(1)->setFrequencyRepair(muR2);
}

DoubleVector GoMarkovOperator17::calcTempOutputMarkovStatusCorrelate1(DoubleVector PS1, DoubleVector PS2)
{
    Q_UNUSED(PS2);
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector QC = 1.0 - PC;
    DoubleVector G1 = PC;
    DoubleVector G2 = PS1 * QC;
    return G1 / (G1 + G2);
}

DoubleVector GoMarkovOperator17::calcTempOutputMarkovStatusCorrelate2(DoubleVector PS1, DoubleVector PS2)
{
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector QS1 = 1.0 - PS1;
    DoubleVector QS2 = 1.0 - PS2;
    DoubleVector QC = 1.0 - PC;
    DoubleVector G3 = PS1 * PS2 * PC;
    DoubleVector G4 = QS1 * PS2 * PC + QS2 * PS1 * PC + QC * PS1 * PS2;
    return G3 / (G3 + G4);
}
