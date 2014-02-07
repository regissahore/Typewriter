#include "qmath.h"
#include "GoMarkovOperator9b2.h"
#include "GoMarkovStatus.h"

GoMarkovOperator9B2::GoMarkovOperator9B2() : GoMarkovOperator9B()
{
}

GoMarkovOperator9B2::~GoMarkovOperator9B2()
{
    this->GoMarkovOperator9B::~GoMarkovOperator9B();
}

void GoMarkovOperator9B2::calcOutputMarkovStatus(double time)
{
    DoubleVector lambdaS = lambdaS1 + lambdaS2;
    DoubleVector muS = (lambdaS1 + lambdaS2) * muS1 * muS2 / (muS1 * lambdaS2 + muS2 * lambdaS1 + lambdaS1 * lambdaS2);
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
    DoubleVector QR = 1.0 - PR;
    DoubleVector lambdaR = lambdaS + lambdaE;
    DoubleVector muR = lambdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GoMarkovOperator9B2::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    DoubleVector lambdaS = lambdaS1 + lambdaS2;
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector lambdaF = this->feedbackStatus()->frequencyBreakdown();
    DoubleVector lambdaE = lambdaC + lambdaF;
    DoubleVector QR = 1.0 - PR[0];
    DoubleVector lambdaR = lambdaS + lambdaE;
    DoubleVector muR = lambdaR * PR[0] / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GoMarkovOperator9B2::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(input);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    DoubleVector lambdaS = lambdaS1 + lambdaS2;
    DoubleVector muS = (lambdaS1 + lambdaS2) * muS1 * muS2 / (muS1 * lambdaS2 + muS2 * lambdaS1 + lambdaS1 * lambdaS2);
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
