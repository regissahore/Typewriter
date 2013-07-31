#include <qmath.h>
#include "gomarkovoperator20.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator20::GOMarkovOperator20() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(1);
    this->output()->setNumber(1);
}

GOMarkovOperator20::~GOMarkovOperator20()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator20::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GOMarkovStatus *status1 = this->getPrevMarkovStatus();
    GOMarkovStatus *status2 = this->getPrevSubMarkovStatus();
    double PS1 = status1->probabilityNormal();
    double PS2 = status2->probabilityNormal();
    double lambdaS1 = status1->frequencyBreakdown();
    double lambdaS2 = status2->frequencyBreakdown();
    double PR = PS1 - PS2;
    if (PR < 0.0)
    {
        PR = 0.0;
    }
    double QR = 1.0 - PR;
    double lambdaR = lambdaS1 + lambdaS2;
    double muR = lambdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator20::calcCommonOutputMarkovStatus(QVector<double> PR)
{
    GOMarkovStatus *status1 = this->getPrevMarkovStatus();
    GOMarkovStatus *status2 = this->getPrevSubMarkovStatus();
    double lambdaS1 = status1->frequencyBreakdown();
    double lambdaS2 = status2->frequencyBreakdown();
    double QR = 1.0 - PR[0];
    double lambdaR = lambdaS1 + lambdaS2;
    double muR = lambdaR * PR[0] / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator20::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(index);
    double PS1 = input[0];
    double PS2 = subInput[0];
    double PR = PS1 - PS2;
    if (PR < 0.0)
    {
        PR = 0.0;
    }
    return PR;
}
