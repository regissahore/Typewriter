#include <QObject>
#include <qmath.h>
#include "GoMarkovOperatorSplitPoint.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"
#include "Messager.h"
#include "MessageFactory.h"
#include "GoMarkovOperatorFactory.h"

GoMarkovOperatorSplitPoint::GoMarkovOperatorSplitPoint() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(3);
}

GoMarkovOperatorSplitPoint::~GoMarkovOperatorSplitPoint()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperatorSplitPoint::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GoMarkovStatus *prevStatus = this->getPrevMarkovStatus();
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

DoubleVector GoMarkovOperatorSplitPoint::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    return input[0].getValue(index);
}
