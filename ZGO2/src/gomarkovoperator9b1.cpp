#include "qmath.h"
#include "gomarkovoperator9b1.h"
#include "gomarkovstatus.h"

GOMarkovOperator9B1::GOMarkovOperator9B1() : GOMarkovOperator9B()
{
}

GOMarkovOperator9B1::~GOMarkovOperator9B1()
{
    this->GOMarkovOperator9B::~GOMarkovOperator9B();
}

void GOMarkovOperator9B1::calcOutputMarkovStatus(double time)
{
    GOMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    double lambdaS1 = status1->frequencyBreakdown();
    double muS1 = status1->frequencyRepair();
    GOMarkovStatus *status2 = this->getPrevMarkovStatus(1);
    double lambdaS2 = status2->frequencyBreakdown();
    double muS2 = status2->frequencyRepair();
    double lambdaS = lambdaS1 + lambdaS2;
    double muS = (lambdaS1 + lambdaS2) * muS1 * muS2 / (muS1 * lambdaS2 + muS2 * lambdaS1 + lambdaS1 * lambdaS2);
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double muC = this->markovStatus()->frequencyRepair();
    double lambdaF = this->markovFeedbackStatus()->frequencyBreakdown();
    double muF = this->markovFeedbackStatus()->frequencyRepair();
    double lambdaE = lambdaC + lambdaF;
    double muE = lambdaE * muC * muF / (lambdaC * muF + lambdaF * muC);
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

void GOMarkovOperator9B1::calcCommonOutputMarkovStatus(QVector<double> PR)
{
    GOMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    double lambdaS1 = status1->frequencyBreakdown();
    GOMarkovStatus *status2 = this->getPrevMarkovStatus(1);
    double lambdaS2 = status2->frequencyBreakdown();
    double lambdaS = lambdaS1 + lambdaS2;
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double lambdaF = this->markovFeedbackStatus()->frequencyBreakdown();
    double lambdaE = lambdaC + lambdaF;
    double QR = 1.0 - PR[0];
    double lambdaR = lambdaS + lambdaE;
    double muR = lambdaR * PR[0] / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator9B1::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(input);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    GOMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    double lambdaS1 = status1->frequencyBreakdown();
    double muS1 = status1->frequencyRepair();
    GOMarkovStatus *status2 = this->getPrevMarkovStatus(1);
    double lambdaS2 = status2->frequencyBreakdown();
    double muS2 = status2->frequencyRepair();
    double lambdaS = lambdaS1 + lambdaS2;
    double muS = (lambdaS1 + lambdaS2) * muS1 * muS2 / (muS1 * lambdaS2 + muS2 * lambdaS1 + lambdaS1 * lambdaS2);
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double muC = this->markovStatus()->frequencyRepair();
    double lambdaF = this->markovFeedbackStatus()->frequencyBreakdown();
    double muF = this->markovFeedbackStatus()->frequencyRepair();
    double lambdaE = lambdaC + lambdaF;
    double muE = lambdaE * muC * muF / (lambdaC * muF + lambdaF * muC);
    double PR = (muS * muE +
                 lambdaE * muS * exp(-(muE + lambdaE) * time) +
                 lambdaS * muE * exp(-(muS + lambdaS) * time) +
                 lambdaS * lambdaE * exp(-(muE + lambdaE + muS + lambdaS) * time)) /
            ((muS + lambdaS) * (muE + lambdaE));
    return PR;
}
