#include <qmath.h>
#include "gomarkovoperator12a.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator12A::GOMarkovOperator12A() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(3);
}

GOMarkovOperator12A::~GOMarkovOperator12A()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator12A::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GOMarkovOperator *prevOperator = this->getPrevOperator();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = prevOperator->markovOutputStatus()->at(i);
        double PR = prevStatus->probabilityNormal();
        double lambdaR = prevStatus->frequencyBreakdown();
        double muR = prevStatus->frequencyRepair();
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

double GOMarkovOperator12A::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    return input[index];
}
