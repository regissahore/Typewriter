#include <qmath.h>
#include "GoMarkovOperator5.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator5::GoMarkovOperator5() : GoMarkovOperator()
{
    this->input()->setNumber(0);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator5::~GoMarkovOperator5()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator5::calcQualitativeProbability()
{
    DoubleVector IC = this->qualitativeStatus();
    this->_qualitativeOutput[0] = IC;
}

void GoMarkovOperator5::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    DoubleVector PR = this->_markovStatus->probabilityNormal();
    DoubleVector lambdaR = this->_markovStatus->frequencyBreakdown();
    DoubleVector muR = this->_markovStatus->frequencyRepair();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}
