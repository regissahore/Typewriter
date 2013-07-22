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
    GOMarkovOperator *prevOperator = this->getPrevSubOperator();
    double PS1 = status1->probabilityNormal();
    double lambdaS1 = status1->frequencyBreakdown();
    double PC1 = this->markovStatus()->probabilityNormal();
    double lambdaC1 = this->markovStatus()->frequencyBreakdown();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        GOMarkovStatus *status2 = prevOperator->markovOutputStatus()->at(i);
        double PS2 = status2->probabilityNormal();
        double lambdaS2 = status2->frequencyBreakdown();
        double lambda = this->lambda2()->at(i);
        double mu = this->mu2()->at(i);
        double PC2 = mu / (lambda + mu) * (1 + lambda / mu * exp(-(lambda + mu) * time));
        double PR = PS1 * PC1 * PS2 + PS1 * PC2 * PS2;
        double QR = 1.0 - PR;
        double lambdaR = lambdaS1 + lambdaS2 + lambdaC1 + lambda;
        double muR = lambdaR * PR / QR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

void GOMarkovOperator22A::calcCommonOutputMarkovStatus(QVector<double> PR)
{
    GOMarkovStatus *status1 = this->getPrevMarkovStatus();
    GOMarkovOperator *prevOperator = this->getPrevSubOperator();
    double lambdaS1 = status1->frequencyBreakdown();
    double lambdaC1 = this->markovStatus()->frequencyBreakdown();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        GOMarkovStatus *status2 = prevOperator->markovOutputStatus()->at(i);
        double lambdaS2 = status2->frequencyBreakdown();
        double lambda = this->lambda2()->at(i);
        double QR = 1.0 - PR[i];
        double lambdaR = lambdaS1 + lambdaS2 + lambdaC1 + lambda;
        double muR = lambdaR * PR[i] / QR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR[i]);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

double GOMarkovOperator22A::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    double PS1 = input[0];
    double PC1 = this->markovStatus()->probabilityNormal();
    double PS2 = subInput[index];
    double lambda = this->lambda2()->at(index);
    double mu = this->mu2()->at(index);
    double PC2 = mu / (lambda + mu) * (1 + lambda / mu * exp(-(lambda + mu) * time));
    double PR = PS1 * PC1 * PS2 + PS1 * PC2 * PS2;
    return PR;
}
