#include <qmath.h>
#include "gomarkovoperator9a1.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"
#include "rungekuttamarkov9a1.h"

GOMarkovOperator9A1::GOMarkovOperator9A1() : GOMarkovOperator9A()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->_rungeKutta = new RungeKuttaMarkov9A1();
}

GOMarkovOperator9A1::~GOMarkovOperator9A1()
{
    this->GOMarkovOperator9A::~GOMarkovOperator9A();
    delete this->_rungeKutta;
}

void GOMarkovOperator9A1::calcOutputMarkovStatus(double time)
{
    if (this->isBreakdownCorrelate())
    {
        this->calcOutputMarkovStatusBreakdown(time);
    }
    else
    {
        this->calcOutputMarkovStatusNormal(time);
    }
}

double GOMarkovOperator9A1::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(input);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    if (this->isBreakdownCorrelate())
    {
        return this->calcTempOutputMarkovStatusBreakdown(time);
    }
    return this->calcTempOutputMarkovStatusNormal(time);
}

void GOMarkovOperator9A1::calcOutputMarkovStatusNormal(double time)
{
    GOMarkovStatus *status = this->getPrevMarkovStatus();
    double lambda1 = status->frequencyBreakdown();
    double mu1 = status->frequencyRepair();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double muC = this->markovStatus()->frequencyRepair();
    double lambdaF = this->markovStatus()->frequencyBreakdown();
    double muF = this->markovStatus()->frequencyRepair();
    double lambda2 = lambdaC + lambdaF;
    double mu2 = lambda2 * muC * muF / (lambdaC * muF + lambdaF * muC);
    double s1 = 0.5 * (-(lambda1 + lambda2 + mu1 + mu2) + sqrt((lambda1 - lambda2 + mu1 - mu2) * (lambda1 - lambda2 + mu1 - mu2) + 4 * lambda1 * lambda2));
    double s2 = 0.5 * (-(lambda1 + lambda2 + mu1 + mu2) - sqrt((lambda1 - lambda2 + mu1 - mu2) * (lambda1 - lambda2 + mu1 - mu2) + 4 * lambda1 * lambda2));
    double PR = mu1 * mu2 / s1 / s2 +
            (s1 * s1 + (mu1 + mu2) * s1 + mu1 * mu2) / (s1 * (s1 - s2)) * exp(s1 * time) +
            (s2 * s2 + (mu1 + mu2) * s2 + mu1 * mu2) / (s2 * (s2 - s1)) * exp(s2 * time);
    double QR = 1.0 - PR;
    double lambdaR = lambda1 + lambda2;
    double muR = lambdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator9A1::calcTempOutputMarkovStatusNormal(double time)
{
    GOMarkovStatus *status = this->getPrevMarkovStatus();
    double lambda1 = status->frequencyBreakdown();
    double mu1 = status->frequencyRepair();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double muC = this->markovStatus()->frequencyRepair();
    double lambdaF = this->markovStatus()->frequencyBreakdown();
    double muF = this->markovStatus()->frequencyRepair();
    double lambda2 = lambdaC + lambdaF;
    double mu2 = lambda2 * muC * muF / (lambdaC * muF + lambdaF * muC);
    double s1 = 0.5 * (-(lambda1 + lambda2 + mu1 + mu2) + sqrt((lambda1 - lambda2 + mu1 - mu2) * (lambda1 - lambda2 + mu1 - mu2) + 4 * lambda1 * lambda2));
    double s2 = 0.5 * (-(lambda1 + lambda2 + mu1 + mu2) - sqrt((lambda1 - lambda2 + mu1 - mu2) * (lambda1 - lambda2 + mu1 - mu2) + 4 * lambda1 * lambda2));
    double PR = mu1 * mu2 / s1 / s2 +
            (s1 * s1 + (mu1 + mu2) * s1 + mu1 * mu2) / (s1 * (s1 - s2)) * exp(s1 * time) +
            (s2 * s2 + (mu1 + mu2) * s2 + mu1 * mu2) / (s2 * (s2 - s1)) * exp(s2 * time);
    return PR;
}

void GOMarkovOperator9A1::calcOutputMarkovStatusBreakdown(double time)
{
    GOMarkovStatus *status = this->getPrevMarkovStatus();
    double lambda1 = status->frequencyBreakdown();
    double mu1 = status->frequencyRepair();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double muC = this->markovStatus()->frequencyRepair();
    double lambdaF = this->markovStatus()->frequencyBreakdown();
    double muF = this->markovStatus()->frequencyRepair();
    double lambda2 = lambdaC + lambdaF;
    double mu2 = lambda2 * muC * muF / (lambdaC * muF + lambdaF * muC);
    double PR = this->_rungeKutta->calcNormalProbability(time, lambda1, lambda2, mu1, mu2);
    double QR = 1.0 - PR;
    double lambdaR = lambda1 + lambda2;
    double muR = lambdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator9A1::calcTempOutputMarkovStatusBreakdown(double time)
{
    GOMarkovStatus *status = this->getPrevMarkovStatus();
    double lambda1 = status->frequencyBreakdown();
    double mu1 = status->frequencyRepair();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double muC = this->markovStatus()->frequencyRepair();
    double lambdaF = this->markovStatus()->frequencyBreakdown();
    double muF = this->markovStatus()->frequencyRepair();
    double lambda2 = lambdaC + lambdaF;
    double mu2 = lambda2 * muC * muF / (lambdaC * muF + lambdaF * muC);
    double PR = this->_rungeKutta->calcNormalProbability(time, lambda1, lambda2, mu1, mu2);
    return PR;
}
