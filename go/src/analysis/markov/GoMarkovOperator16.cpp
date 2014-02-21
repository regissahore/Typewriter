#include <qmath.h>
#include "GoMarkovOperator16.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator16::GoMarkovOperator16() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(1);
    this->output()->setNumber(2);
}

GoMarkovOperator16::~GoMarkovOperator16()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator16::calcQualitativeProbability()
{
    DoubleVector IS1 = this->getPrevQualitativeStatus();
    DoubleVector IS2 = this->getPrevSubQualitativeStatus();
    DoubleVector IC = this->qualitativeStatus();
    DoubleVector IR1 = IS1 * IC;
    DoubleVector IR2 = IS1 * IS2 * IC;
    this->_qualitativeOutput[0] = IR1;
    this->_qualitativeOutput[1] = IR2;
}

void GoMarkovOperator16::calcOutputMarkovStatus(double time)
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

void GoMarkovOperator16::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
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

DoubleVector GoMarkovOperator16::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
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

void GoMarkovOperator16::calcOutputMarkovStatusNormal()
{
    GoMarkovStatus* status1 = this->getPrevMarkovStatus();
    GoMarkovStatus* status2 = this->getPrevSubMarkovStatus();
    DoubleVector PS1 = status1->probabilityNormal();
    DoubleVector PS2 = status2->probabilityNormal();
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector PR1 = PS1 * PC;
    DoubleVector PR2 = PS1 * PS2 * PC;
    DoubleVector QR1 = 1.0 - PR1;
    DoubleVector QR2 = 1.0 - PR2;
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector lambdaR1 = lambdaS1 + lambdaC;
    DoubleVector muR1 = lambdaR1 * PR1 / QR1;
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

void GoMarkovOperator16::calcCommonOutputMarkovStatusNormal(QVector<DoubleVector> PR)
{
    GoMarkovStatus* status1 = this->getPrevMarkovStatus();
    GoMarkovStatus* status2 = this->getPrevSubMarkovStatus();
    DoubleVector PR1 = PR[0];
    DoubleVector PR2 = PR[1];
    DoubleVector QR1 = 1.0 - PR1;
    DoubleVector QR2 = 1.0 - PR2;
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector lambdaR1 = lambdaS1 + lambdaC;
    DoubleVector muR1 = lambdaR1 * PR1 / QR1;
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

DoubleVector GoMarkovOperator16::calcTempOutputMarkovStatusNormal1(DoubleVector PS1, DoubleVector PS2)
{
    Q_UNUSED(PS2);
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    return PS1 * PC;
}

DoubleVector GoMarkovOperator16::calcTempOutputMarkovStatusNormal2(DoubleVector PS1, DoubleVector PS2)
{
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    return PS1 * PS2 * PC;
}

void GoMarkovOperator16::calcOutputMarkovStatusCorrelate()
{
    GoMarkovStatus* status1 = this->getPrevMarkovStatus();
    GoMarkovStatus* status2 = this->getPrevSubMarkovStatus();
    DoubleVector PS1 = status1->probabilityNormal();
    DoubleVector PS2 = status2->probabilityNormal();
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector QS1 = 1.0 - PS1;
    DoubleVector QS2 = 1.0 - PS2;
    DoubleVector QC = 1.0 - PC;
    DoubleVector G1 = PS1 * PC;
    DoubleVector G2 = QS1 * PC + QC * PS1;
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

void GoMarkovOperator16::calcCommonOutputMarkovStatusCorrelate(QVector<DoubleVector> PR)
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

DoubleVector GoMarkovOperator16::calcTempOutputMarkovStatusCorrelate1(DoubleVector PS1, DoubleVector PS2)
{
    Q_UNUSED(PS2);
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector QS1 = 1.0 - PS1;
    DoubleVector QC = 1.0 - PC;
    DoubleVector G1 = PS1 * PC;
    DoubleVector G2 = QS1 * PC + QC * PS1;
    return G1 / (G1 + G2);
}

DoubleVector GoMarkovOperator16::calcTempOutputMarkovStatusCorrelate2(DoubleVector PS1, DoubleVector PS2)
{
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector QS1 = 1.0 - PS1;
    DoubleVector QS2 = 1.0 - PS2;
    DoubleVector QC = 1.0 - PC;
    DoubleVector G3 = PS1 * PS2 * PC;
    DoubleVector G4 = QS1 * PS2 * PC + QS2 * PS1 * PC + QC * PS1 * PS2;
    return G3 / (G3 + G4);
}
