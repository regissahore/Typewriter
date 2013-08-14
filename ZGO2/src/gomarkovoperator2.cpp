#include <qmath.h>
#include "gomarkovoperator2.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator2::GOMarkovOperator2() : GOMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator2::~GOMarkovOperator2()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator2::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    DoubleVector QR = 1.0;
    DoubleVector miuR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector QSi = prevStatus->probabilityBreakdown();
        DoubleVector miuSi = prevStatus->frequencyRepair();
        QR *= QSi;
        miuR += miuSi;
    }
    DoubleVector PR = 1 - QR;
    DoubleVector lambdaR = miuR * QR / PR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

void GOMarkovOperator2::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    DoubleVector QR = 1.0 - PR[0];
    DoubleVector miuR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector QSi = prevStatus->probabilityBreakdown();
        DoubleVector miuSi = prevStatus->frequencyRepair();
        QR *= QSi;
        miuR += miuSi;
    }
    DoubleVector lambdaR = miuR * QR / PR[0];
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

DoubleVector GOMarkovOperator2::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
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
