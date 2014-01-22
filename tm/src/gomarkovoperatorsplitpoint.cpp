#include <QObject>
#include <qmath.h>
#include "gomarkovoperatorsplitpoint.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"
#include "messager.h"
#include "messagefactory.h"
#include "gomarkovoperatorfactory.h"

GOMarkovOperatorSplitPoint::GOMarkovOperatorSplitPoint() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(3);
}

GOMarkovOperatorSplitPoint::~GOMarkovOperatorSplitPoint()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperatorSplitPoint::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GOMarkovStatus *prevStatus = this->getPrevMarkovStatus();
    DoubleVector PR = prevStatus->probabilityNormal();
    DoubleVector lambdaR = prevStatus->frequencyBreakdown();
    DoubleVector muR = prevStatus->frequencyRepair();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR.getValue(i));
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR.getValue(i));
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR.getValue(i));
    }
}

DoubleVector GOMarkovOperatorSplitPoint::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    return input[0].getValue(index);
}
