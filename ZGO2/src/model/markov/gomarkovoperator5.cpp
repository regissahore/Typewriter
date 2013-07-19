#include <qmath.h>
#include "gomarkovoperator5.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator5::GOMarkovOperator5() : GOMarkovOperator()
{
    this->input()->setNumber(0);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator5::~GOMarkovOperator5()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator5::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    this->initOutputMarkovStatus();
    GOMarkovStatus *status = this->_markovStatus;
    double PR = this->_markovStatus->probabilityNormal();
    double lambdaR = this->_markovStatus->frequencyBreakdown();
    double miuR = this->_markovStatus->frequencyRepair();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}
