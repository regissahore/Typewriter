#include "qmath.h"
#include "GoMarkovOperator9b1.h"
#include "GoMarkovStatus.h"

GoMarkovOperator9B1::GoMarkovOperator9B1() : GoMarkovOperator9B()
{
}

GoMarkovOperator9B1::~GoMarkovOperator9B1()
{
    this->GoMarkovOperator9B::~GoMarkovOperator9B();
}

void GoMarkovOperator9B1::calcOutputMarkovStatus(double time)
{
    GoMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector muS1 = status1->frequencyRepair();
    GoMarkovStatus *status2 = this->getPrevMarkovStatus(1);
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector muS2 = status2->frequencyRepair();
    DoubleVector lambdaS = lambdaS1 + lambdaS2;
    DoubleVector muS = (lambdaS1 + lambdaS2) * muS1 * muS2 / (muS1 * lambdaS2 + muS2 * lambdaS1 + lambdaS1 * lambdaS2);
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector muC = this->markovStatus()->frequencyRepair();
    DoubleVector lambdaF = this->markovFeedbackStatus()->frequencyBreakdown();
    DoubleVector muF = this->markovFeedbackStatus()->frequencyRepair();
    DoubleVector lambdaE = lambdaC + lambdaF;
    DoubleVector muE = lambdaE * muC * muF / (lambdaC * muF + lambdaF * muC);
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

void GoMarkovOperator9B1::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    GoMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    GoMarkovStatus *status2 = this->getPrevMarkovStatus(1);
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector lambdaS = lambdaS1 + lambdaS2;
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector lambdaF = this->markovFeedbackStatus()->frequencyBreakdown();
    DoubleVector lambdaE = lambdaC + lambdaF;
    DoubleVector QR = 1.0 - PR[0];
    DoubleVector lambdaR = lambdaS + lambdaE;
    DoubleVector muR = lambdaR * PR[0] / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GoMarkovOperator9B1::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(input);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    GoMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector muS1 = status1->frequencyRepair();
    GoMarkovStatus *status2 = this->getPrevMarkovStatus(1);
    DoubleVector lambdaS2 = status2->frequencyBreakdown();
    DoubleVector muS2 = status2->frequencyRepair();
    DoubleVector lambdaS = lambdaS1 + lambdaS2;
    DoubleVector muS = (lambdaS1 + lambdaS2) * muS1 * muS2 / (muS1 * lambdaS2 + muS2 * lambdaS1 + lambdaS1 * lambdaS2);
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector muC = this->markovStatus()->frequencyRepair();
    DoubleVector lambdaF = this->markovFeedbackStatus()->frequencyBreakdown();
    DoubleVector muF = this->markovFeedbackStatus()->frequencyRepair();
    DoubleVector lambdaE = lambdaC + lambdaF;
    DoubleVector muE = lambdaE * muC * muF / (lambdaC * muF + lambdaF * muC);
    DoubleVector PR = (muS * muE +
                 lambdaE * muS * DoubleVector::Exp(-(muE + lambdaE) * time) +
                 lambdaS * muE * DoubleVector::Exp(-(muS + lambdaS) * time) +
                 lambdaS * lambdaE * DoubleVector::Exp(-(muE + lambdaE + muS + lambdaS) * time)) /
            ((muS + lambdaS) * (muE + lambdaE));
    return PR;
}
