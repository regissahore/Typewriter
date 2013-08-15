#include <qmath.h>
#include "gomarkovoperator22a.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator22A::GOMarkovOperator22A() : GOMarkovOperator22()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(1);
    this->output()->setNumber(3);
}

GOMarkovOperator22A::~GOMarkovOperator22A()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator22A::calcOutputMarkovStatus(double time)
{
    GOMarkovStatus *status1 = this->getPrevMarkovStatus();
    GOMarkovStatus *status2 = this->getPrevSubMarkovStatus();
    DoubleVector PS1 = status1->probabilityNormal();
    DoubleVector PS2 = status2->probabilityNormal();
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector PC1 = this->markovStatus()->probabilityNormal();
    DoubleVector lambdaC1 = this->markovStatus()->frequencyBreakdown();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        double lambda = this->lambda2()->at(i);
        double mu = this->mu2()->at(i);
        DoubleVector PC2 = mu / (lambda + mu) * (1 + lambda / mu * exp(-(lambda + mu) * time));
        DoubleVector PR = PS1 * PC1 * PS2.getValue(i) + PS1 * PC2 * PS2.getValue(i);
        DoubleVector QR = 1.0 - PR;
        DoubleVector lambdaR = lambdaS1 + lambdaS2.getValue(i) + lambdaC1 + lambda;
        DoubleVector muR = lambdaR * PR / QR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

void GOMarkovOperator22A::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    GOMarkovStatus *status1 = this->getPrevMarkovStatus();
    GOMarkovStatus *status2 = this->getPrevSubMarkovStatus();
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector lambdaC1 = this->markovStatus()->frequencyBreakdown();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        double lambda = this->lambda2()->at(i);
        DoubleVector QR = 1.0 - PR[i];
        DoubleVector lambdaR = lambdaS1 + lambdaS2.getValue(i) + lambdaC1 + lambda;
        DoubleVector muR = lambdaR * PR[i] / QR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR[i]);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

DoubleVector GOMarkovOperator22A::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    DoubleVector PS1 = input[0];
    DoubleVector PC1 = this->markovStatus()->probabilityNormal();
    DoubleVector PS2 = subInput[0];
    double lambda = this->lambda2()->at(index);
    double mu = this->mu2()->at(index);
    DoubleVector PC2 = mu / (lambda + mu) * (1 + lambda / mu * exp(-(lambda + mu) * time));
    DoubleVector PR = PS1 * PC1 * PS2.getValue(index) + PS1 * PC2 * PS2.getValue(index);
    return PR;
}
