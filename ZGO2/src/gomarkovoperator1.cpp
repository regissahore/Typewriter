#include <qmath.h>
#include "gomarkovoperator1.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator1::GOMarkovOperator1() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator1::~GOMarkovOperator1()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator1::calcOutputMarkovStatus(double time)
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

DoubleVector GOMarkovOperator1::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    if (this->isBreakdownCorrelate())
    {
        return this->calcTempOutputMarkovStatusCorrelate(input[0]);
    }
    return this->calcTempOutputMarkovStatusNormal(input[0]);
}

void GOMarkovOperator1::calcOutputMarkovStatusNormal()
{
    GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(0);
    DoubleVector PS = prevStatus->probabilityNormal();
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector PR = PS * PC;
    DoubleVector QR = 1.0 - PR;
    DoubleVector lamdaS = prevStatus->frequencyBreakdown();
    DoubleVector lamdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector lamdaR = lamdaS + lamdaC;
    DoubleVector miuR = lamdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

DoubleVector GOMarkovOperator1::calcTempOutputMarkovStatusNormal(DoubleVector PS)
{
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    return PS * PC;
}

void GOMarkovOperator1::calcOutputMarkovStatusCorrelate()
{
    GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(0);
    DoubleVector PS = prevStatus->probabilityNormal();
    DoubleVector QS = prevStatus->probabilityBreakdown();
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector QC = this->markovStatus()->probabilityBreakdown();
    DoubleVector G1 = PS * PC;
    DoubleVector G2 = PS * QC + QS * PC;
    DoubleVector PR = G1 / (G1 + G2);
    DoubleVector lamdaS = prevStatus->frequencyBreakdown();
    DoubleVector miuS = prevStatus->frequencyRepair();
    DoubleVector lamdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector miuC = this->markovStatus()->frequencyRepair();
    DoubleVector lamdaR = lamdaS + lamdaC;
    DoubleVector miuR = lamdaR / (lamdaS / miuS + lamdaC / miuC);
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

DoubleVector GOMarkovOperator1::calcTempOutputMarkovStatusCorrelate(DoubleVector PS)
{
    DoubleVector QS = 1.0 - PS;
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector QC = 1.0 - PC;
    DoubleVector G1 = PS * PC;
    DoubleVector G2 = PS * QC + QS * PC;
    return G1 / (G1 + G2);
}
