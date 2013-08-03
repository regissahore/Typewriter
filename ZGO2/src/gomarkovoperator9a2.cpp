#include <qmath.h>
#include "gomarkovoperator9a2.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator9A2::GOMarkovOperator9A2() : GOMarkovOperator9A()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator9A2::~GOMarkovOperator9A2()
{
    this->GOMarkovOperator9A::~GOMarkovOperator9A();
}

void GOMarkovOperator9A2::calcOutputMarkovStatus(double time)
{
    GOMarkovStatus *status = this->getPrevMarkovStatus();
    double lambdaS = status->frequencyBreakdown();
    double muS = status->frequencyRepair();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double muC = this->markovStatus()->frequencyRepair();
    double lambdaF = this->markovFeedbackStatus()->frequencyBreakdown();
    double muF = this->markovFeedbackStatus()->frequencyRepair();
    double lambdaE = lambdaC + lambdaF;
    double muE = lambdaE * muC * muF / (lambdaC * muF + lambdaF * muC + lambdaC * lambdaF);
    double PR = (muS * muE +
                 lambdaE * muS * exp(-(muE + lambdaE) * time) +
                 lambdaS * muE * exp(-(muS + lambdaS) * time) +
                 lambdaS * lambdaE * exp(-(muE + lambdaE + muS + lambdaS) * time)) /
            ((muS + lambdaS) * (muE + lambdaE));
    double QR = 1.0 - PR;
    double lambdaR = lambdaS + lambdaE;
    double muR = lambdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator9A2::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(input);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    GOMarkovStatus *status = this->getPrevMarkovStatus();
    double lambdaS = status->frequencyBreakdown();
    double muS = status->frequencyRepair();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double muC = this->markovStatus()->frequencyRepair();
    double lambdaF = this->markovFeedbackStatus()->frequencyBreakdown();
    double muF = this->markovFeedbackStatus()->frequencyRepair();
    double lambdaE = lambdaC + lambdaF;
    double muE = lambdaE * muC * muF / (lambdaC * muF + lambdaF * muC + lambdaC * lambdaF);
    double PR = (muS * muE +
                 lambdaE * muS * exp(-(muE + lambdaE) * time) +
                 lambdaS * muE * exp(-(muS + lambdaS) * time) +
                 lambdaS * lambdaE * exp(-(muE + lambdaE + muS + lambdaS) * time)) /
            ((muS + lambdaS) * (muE + lambdaE));
    return PR;
}
