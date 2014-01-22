#include <qmath.h>
#include "GoMarkovOperator15a.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator15A::GoMarkovOperator15A() : GoMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(3);
}

GoMarkovOperator15A::~GoMarkovOperator15A()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator15A::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    this->initOutputMarkovStatus();
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector PS = prevStatus->probabilityNormal();
        DoubleVector PC = this->markovStatus()->probabilityNormal();
        DoubleVector PR = PS * PC;
        DoubleVector QR = 1 - PR;
        DoubleVector lambdaS = prevStatus->frequencyBreakdown();
        DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
        DoubleVector lambdaR = lambdaS + lambdaC;
        DoubleVector muR = lambdaR * PR / QR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

DoubleVector GoMarkovOperator15A::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    DoubleVector PS = input[index];
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    return PS * PC;
}
