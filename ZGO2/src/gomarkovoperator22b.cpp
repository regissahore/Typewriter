#include <qmath.h>
#include "gomarkovoperator22b.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator22B::GOMarkovOperator22B() : GOMarkovOperator22()
{
    this->input()->setNumber(2);
    this->subInput()->setNumber(1);
    this->output()->setNumber(3);
}

GOMarkovOperator22B::~GOMarkovOperator22B()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator22B::calcOutputMarkovStatus(double time)
{
    GOMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    GOMarkovStatus *status2 = this->getPrevSubMarkovStatus();
    GOMarkovStatus *status3 = this->getPrevMarkovStatus(1);
    DoubleVector PS1 = status1->probabilityNormal();
    DoubleVector PS2 = status2->probabilityNormal();
    DoubleVector PS3 = status3->probabilityNormal();
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector lambdaS3 = status3->frequencyBreakdown();
    DoubleVector PC1 = this->markovStatus()->probabilityNormal();
    DoubleVector lambdaC1 = this->markovStatus()->frequencyBreakdown();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        double lambda = this->lambda2()->at(i);
        double mu = this->mu2()->at(i);
        DoubleVector PC2 = mu / (lambda + mu) * (1 + lambda / mu * exp(-(lambda + mu) * time));
        DoubleVector PR = PS1 * PS3 * PC1 * PS2.getValue(i) + PS1 * PS3 * PC2 * PS2.getValue(i);
        DoubleVector QR = 1.0 - PR;
        DoubleVector lambdaR = lambdaS1 + lambdaS2.getValue(i) + lambdaS3 + lambdaC1 + lambda;
        DoubleVector muR = lambdaR * PR / QR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

void GOMarkovOperator22B::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    GOMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    GOMarkovStatus *status2 = this->getPrevSubMarkovStatus();
    GOMarkovStatus *status3 = this->getPrevMarkovStatus(1);
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector lambdaS3 = status3->frequencyBreakdown();
    DoubleVector lambdaC1 = this->markovStatus()->frequencyBreakdown();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        double lambda = this->lambda2()->at(i);
        DoubleVector QR = 1.0 - PR[i];
        DoubleVector lambdaR = lambdaS1 + lambdaS2.getValue(0) + lambdaS3 + lambdaC1 + lambda;
        DoubleVector muR = lambdaR * PR[i] / QR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR[i]);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

DoubleVector GOMarkovOperator22B::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(index);
    DoubleVector PS1 = input[0];
    DoubleVector PS2 = subInput[0];
    DoubleVector PS3 = input[2];
    DoubleVector PC1 = this->markovStatus()->probabilityNormal();
    double lambda = this->lambda2()->at(index);
    double mu = this->mu2()->at(index);
    DoubleVector PC2 = mu / (lambda + mu) * (1 + lambda / mu * exp(-(lambda + mu) * time));
    DoubleVector PR = PS1 * PS3 * PC1 * PS2.getValue(index) + PS1 * PS3 * PC2 * PS2.getValue(index);
    return PR;
}
