#include <qmath.h>
#include "gomarkovoperator15a.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator15A::GOMarkovOperator15A() : GOMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(3);
}

GOMarkovOperator15A::~GOMarkovOperator15A()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator15A::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    this->initOutputMarkovStatus();
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        double PS = prevStatus->probabilityNormal();
        double PC = this->markovStatus()->probabilityNormal();
        double PR = PS * PC;
        double QR = 1 - PR;
        double lambdaS = prevStatus->frequencyBreakdown();
        double lambdaC = this->markovStatus()->frequencyBreakdown();
        double lambdaR = lambdaS + lambdaC;
        double muR = lambdaR * PR / QR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

double GOMarkovOperator15A::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    double PS = input[index];
    double PC = this->markovStatus()->probabilityNormal();
    return PS * PC;
}
