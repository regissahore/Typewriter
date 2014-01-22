#include "gomarkovoperator13b.h"
#include "goinput.h"
#include "gooutput.h"
#include "gomarkovstatus.h"

GOMarkovOperator13B::GOMarkovOperator13B() : GOMarkovOperator13()
{
}

GOMarkovOperator13B::~GOMarkovOperator13B()
{
    this->GOMarkovOperator13::~GOMarkovOperator13();
}

void GOMarkovOperator13B::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    QVector<DoubleVector> PS;
    QVector<DoubleVector> muS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *status = this->getPrevMarkovStatus(i);
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

void GOMarkovOperator13B::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    QVector<DoubleVector> muS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *status = this->getPrevMarkovStatus(i);
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

DoubleVector GOMarkovOperator13B::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
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
