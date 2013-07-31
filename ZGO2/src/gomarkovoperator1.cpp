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

double GOMarkovOperator1::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
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
    double PS = prevStatus->probabilityNormal();
    double PC = this->markovStatus()->probabilityNormal();
    double PR = PS * PC;
    double QR = 1 - PR;
    double lamdaS = prevStatus->frequencyBreakdown();
    double lamdaC = this->markovStatus()->frequencyBreakdown();
    double lamdaR = lamdaS + lamdaC;
    if (this->isDualBreakdown())
    {
        lamdaR += this->markovStatus2()->frequencyBreakdown();
    }
    double miuR = lamdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

double GOMarkovOperator1::calcTempOutputMarkovStatusNormal(double PS)
{
    double PC = this->markovStatus()->probabilityNormal();
    return PS * PC;
}

void GOMarkovOperator1::calcOutputMarkovStatusCorrelate()
{
    GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(0);
    double PS = prevStatus->probabilityNormal();
    double QS = prevStatus->probabilityBreakdown();
    double PC = this->markovStatus()->probabilityNormal();
    double QC = this->markovStatus()->probabilityBreakdown();
    double G1 = PS * PC;
    double G2 = PS * QC + QS * PC;
    double PR = G1 / (G1 + G2);
    double lamdaS = prevStatus->frequencyBreakdown();
    double miuS = prevStatus->frequencyRepair();
    double lamdaC = this->markovStatus()->frequencyBreakdown();
    double miuC = this->markovStatus()->frequencyRepair();
    double lamdaR = lamdaS + lamdaC;
    if (this->isDualBreakdown())
    {
        lamdaR += this->markovStatus2()->frequencyBreakdown();
    }
    double miuR = lamdaR / (lamdaS / miuS + lamdaC / miuC);
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

double GOMarkovOperator1::calcTempOutputMarkovStatusCorrelate(double PS)
{
    double QS = 1 - PS;
    double PC = this->markovStatus()->probabilityNormal();
    double QC = 1 - PC;
    double G1 = PS * PC;
    double G2 = PS * QC + QS * PC;
    return G1 / (G1 + G2);
}
