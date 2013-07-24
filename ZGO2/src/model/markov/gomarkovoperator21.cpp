#include <qmath.h>
#include "gomarkovoperator21.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator21::GOMarkovOperator21() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->initOutputMarkovStatus();
}

GOMarkovOperator21::~GOMarkovOperator21()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator21::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GOMarkovStatus *status = this->getPrevMarkovStatus();
    double PR = status->probabilityNormal();
    double lambdaR = status->frequencyBreakdown();
    double muR = status->frequencyRepair();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
    if (time < 1e-10)
    {
        this->markovOutputStatus()->at(0)->setProbabilityNormal(1.0);
        this->markovOutputStatus()->at(0)->setFrequencyBreakdown(0.0);
        this->markovOutputStatus()->at(0)->setFrequencyRepair(1.0);
    }
}

double GOMarkovOperator21::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    return input[0];
}
