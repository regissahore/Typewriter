#include <qmath.h>
#include "gomarkovoperator15b.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator15B::GOMarkovOperator15B() : GOMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator15B::~GOMarkovOperator15B()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator15B::initOutputMarkovStatus()
{
    for (int i = this->_outputStatus->size(); i < this->input()->number(); ++i)
    {
        this->_outputStatus->push_back(new GOMarkovStatus());
    }
}

void GOMarkovOperator15B::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    this->initOutputMarkovStatus();
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector PR = prevStatus->probabilityNormal();
        DoubleVector lambdaR = prevStatus->frequencyBreakdown();
        DoubleVector muR = prevStatus->frequencyRepair();
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

DoubleVector GOMarkovOperator15B::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    return input[index];
}
