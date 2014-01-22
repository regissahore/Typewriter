#include <qmath.h>
#include "GoMarkovOperator2.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator2::GoMarkovOperator2() : GoMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator2::~GoMarkovOperator2()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator2::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    DoubleVector QR = 1.0;
    DoubleVector miuR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector QSi = prevStatus->probabilityBreakdown();
        DoubleVector miuSi = prevStatus->frequencyRepair();
        QR *= QSi;
        miuR += miuSi;
    }
    DoubleVector PR = 1.0 - QR;
    DoubleVector lambdaR = miuR * QR / PR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

void GoMarkovOperator2::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    DoubleVector QR = 1.0 - PR[0];
    DoubleVector miuR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector QSi = prevStatus->probabilityBreakdown();
        DoubleVector miuSi = prevStatus->frequencyRepair();
        QR *= QSi;
        miuR += miuSi;
    }
    DoubleVector lambdaR = miuR * QR / PR[0];
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

DoubleVector GoMarkovOperator2::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    DoubleVector QR = 1.0;
    for (int i = 0; i < input.size(); ++i)
    {
        QR *= 1.0 - input[i];
    }
    return 1.0 - QR;
}
