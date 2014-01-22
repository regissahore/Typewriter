#include "GoMarkovOperator13b.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoMarkovStatus.h"

GoMarkovOperator13B::GoMarkovOperator13B() : GoMarkovOperator13()
{
}

GoMarkovOperator13B::~GoMarkovOperator13B()
{
    this->GoMarkovOperator13::~GoMarkovOperator13();
}

void GoMarkovOperator13B::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    QVector<DoubleVector> PS;
    QVector<DoubleVector> muS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *status = this->getPrevMarkovStatus(i);
        PS.push_back(status->probabilityNormal());
        muS.push_back(status->frequencyRepair());
    }
    for (int i = 0; i < this->output()->number(); ++i)
    {
        DoubleVector PR = 0.0;
        DoubleVector muR = 0.0;
        for (int j = 0; j < this->input()->number(); ++j)
        {
            if (this->relation()->at(j).at(i))
            {
                PR += PS[j];
                muR += muS[j];
            }
        }
        DoubleVector QR = 1.0 - PR;
        DoubleVector lambdaR = muR * QR / PR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

void GoMarkovOperator13B::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    QVector<DoubleVector> muS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *status = this->getPrevMarkovStatus(i);
        muS.push_back(status->frequencyRepair());
    }
    for (int i = 0; i < this->output()->number(); ++i)
    {
        DoubleVector muR = 0.0;
        for (int j = 0; j < this->input()->number(); ++j)
        {
            if (this->relation()->at(j).at(i))
            {
                muR += muS[j];
            }
        }
        DoubleVector QR = 1.0 - PR[i];
        DoubleVector lambdaR = muR * QR / PR[i];
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR[i]);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

DoubleVector GoMarkovOperator13B::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    QVector<DoubleVector> PS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        PS.push_back(input[i]);
    }
    DoubleVector PR = 0.0;
    for (int j = 0; j < this->input()->number(); ++j)
    {
        if (this->relation()->at(j).at(index))
        {
            PR += PS[j];
        }
    }
    return PR;
}
