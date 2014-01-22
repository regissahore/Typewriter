#include "gomarkovoperator13a.h"
#include "goinput.h"
#include "gooutput.h"
#include "gomarkovstatus.h"

GOMarkovOperator13A::GOMarkovOperator13A() : GOMarkovOperator13()
{
}

GOMarkovOperator13A::~GOMarkovOperator13A()
{
    this->GOMarkovOperator13::~GOMarkovOperator13();
}

void GOMarkovOperator13A::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    QVector<DoubleVector> PS;
    QVector<DoubleVector> lambdaS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *status = this->getPrevMarkovStatus(i);
        PS.push_back(status->probabilityNormal());
        lambdaS.push_back(status->frequencyBreakdown());
    }
    for (int i = 0; i < this->output()->number(); ++i)
    {
        DoubleVector PR = 1.0;
        DoubleVector lambdaR = 0.0;
        for (int j = 0; j < this->input()->number(); ++j)
        {
            if (this->relation()->at(j).at(i))
            {
                PR *= PS[j];
                lambdaR += lambdaS[j];
            }
        }
        DoubleVector QR = 1.0 - PR;
        DoubleVector muR = lambdaR * PR / QR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

void GOMarkovOperator13A::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    QVector<DoubleVector> lambdaS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *status = this->getPrevMarkovStatus(i);
        lambdaS.push_back(status->frequencyBreakdown());
    }
    for (int i = 0; i < this->output()->number(); ++i)
    {
        DoubleVector lambdaR = 0.0;
        for (int j = 0; j < this->input()->number(); ++j)
        {
            if (this->relation()->at(j).at(i))
            {
                lambdaR += lambdaS[j];
            }
        }
        DoubleVector QR = 1.0 - PR[i];
        DoubleVector muR = lambdaR * PR[i] / QR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR[i]);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

DoubleVector GOMarkovOperator13A::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    QVector<DoubleVector> PS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        PS.push_back(input[i]);
    }
    DoubleVector PR = 1.0;
    for (int j = 0; j < this->input()->number(); ++j)
    {
        if (this->relation()->at(j).at(index))
        {
            PR *= PS[j];
        }
    }
    return PR;
}
