#include <qmath.h>
#include "GoMarkovOperator9a2.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator9A2::GoMarkovOperator9A2() : GoMarkovOperator9A()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator9A2::~GoMarkovOperator9A2()
{
    this->GoMarkovOperator9A::~GoMarkovOperator9A();
}

void GoMarkovOperator9A2::calcOutputMarkovStatus(double time)
{
    this->prepareSum();
    DoubleVector lambdaS = lambdaS1;
    DoubleVector muS = muS1;
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector muC = this->markovStatus()->frequencyRepair();
    if (this->breakdownNum() == 1)
    {
        muC = this->markovStatus1()->frequencyRepair();
    }
    DoubleVector lambdaF = this->feedbackStatus()->frequencyBreakdown();
    DoubleVector muF = this->feedbackStatus()->frequencyRepair();
    DoubleVector lambdaE = lambdaC + lambdaF;
    DoubleVector muE = lambdaE * muC * muF / (lambdaC * muF + lambdaF * muC + lambdaC * lambdaF);
    DoubleVector PR = (muS * muE +
                 lambdaE * muS * DoubleVector::Exp(-(muE + lambdaE) * time) +
                 lambdaS * muE * DoubleVector::Exp(-(muS + lambdaS) * time) -
                 lambdaS * lambdaE * DoubleVector::Exp(-(muE + lambdaE + muS + lambdaS) * time)) /
            ((muS + lambdaS) * (muE + lambdaE));
    DoubleVector QR = 1.0 - PR;
    DoubleVector lambdaR = lambdaS + lambdaE;
    DoubleVector muR = lambdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GoMarkovOperator9A2::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(input);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    this->prepareSum();
    DoubleVector lambdaS = lambdaS1;
    DoubleVector muS = muS1;
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector muC = this->markovStatus()->frequencyRepair();
    DoubleVector lambdaF = this->feedbackStatus()->frequencyBreakdown();
    DoubleVector muF = this->feedbackStatus()->frequencyRepair();
    DoubleVector lambdaE = lambdaC + lambdaF;
    DoubleVector muE = lambdaE * muC * muF / (lambdaC * muF + lambdaF * muC + lambdaC * lambdaF);
    DoubleVector PR = (muS * muE +
                 lambdaE * muS * DoubleVector::Exp(-(muE + lambdaE) * time) +
                 lambdaS * muE * DoubleVector::Exp(-(muS + lambdaS) * time) +
                 lambdaS * lambdaE * DoubleVector::Exp(-(muE + lambdaE + muS + lambdaS) * time)) /
            ((muS + lambdaS) * (muE + lambdaE));
    return PR;
}
