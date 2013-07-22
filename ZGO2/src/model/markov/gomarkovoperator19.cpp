#include <qmath.h>
#include "gomarkovoperator19.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator19::GOMarkovOperator19() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(2);
}

GOMarkovOperator19::~GOMarkovOperator19()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator19::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GOMarkovOperator *prevOperator = this->getPrevOperator();
    QVector<double> PS;
    QVector<double> lambdaS;
    QVector<double> muS;
    int N = prevOperator->markovOutputStatus()->size();
    for (int i = 0; i < N; ++i)
    {
        GOMarkovStatus *status = prevOperator->markovOutputStatus()->at(i);
        PS.push_back(status->probabilityNormal());
        lambdaS.push_back(status->frequencyBreakdown());
        muS.push_back(status->frequencyRepair());
    }
    double PC = this->markovStatus()->probabilityNormal();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double PR2 = 0.0;
    double lambdaR2 = 0.0;
    double muR2 = 0.0;
    for (int i = 1; i < N - 1; ++i)
    {
        PR2 += PS[i] * PC;
        lambdaR2 += (lambdaS[i] + lambdaC) * PS[i] * PC;
        muR2 += lambdaS[i] + lambdaC;
    }
    double QR2 = 1.0 - PR2;
    muR2 *= PR2 / QR2;
    double PR1 = PR2 + PS[0];
    double lambdaR1 = lambdaR2 + lambdaS[0] * PS[0];
    lambdaR2 /= PR2;
    lambdaR1 /= PR1;
    double muR1 = muR2 + muS[0];
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR1);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR1);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR1);
    this->markovOutputStatus()->at(1)->setProbabilityNormal(PR2);
    this->markovOutputStatus()->at(1)->setFrequencyBreakdown(lambdaR2);
    this->markovOutputStatus()->at(1)->setFrequencyRepair(muR2);
}

double GOMarkovOperator19::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    QVector<double> PS;
    int N = input.size();
    for (int i = 0; i < N; ++i)
    {
        PS.push_back(input[i]);
    }
    double PC = this->markovStatus()->probabilityNormal();
    double PR2 = 0.0;
    for (int i = 1; i < N - 1; ++i)
    {
        PR2 += PS[i] * PC;
    }
    double PR1 = PR2 + PS[0];
    if (index == 0)
    {
        return PR1;
    }
    return PR2;
}
