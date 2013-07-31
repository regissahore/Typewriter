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
    QVector<double> PS;
    QVector<double> lambdaS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *status = this->getPrevMarkovStatus(i);
        PS.push_back(status->probabilityNormal());
        lambdaS.push_back(status->frequencyBreakdown());
    }
    for (int i = 0; i < this->output()->number(); ++i)
    {
        double PR = 1.0;
        double lambdaR = 0.0;
        for (int j = 0; j < this->input()->number(); ++j)
        {
            if (this->relation()->at(j).at(i))
            {
                PR *= PS[j];
                lambdaR += lambdaS[j];
            }
        }
        double QR = 1.0 - PR;
        double muR = lambdaR * PR / QR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

void GOMarkovOperator13A::calcCommonOutputMarkovStatus(QVector<double> PR)
{
    QVector<double> lambdaS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *status = this->getPrevMarkovStatus(i);
        lambdaS.push_back(status->frequencyBreakdown());
    }
    for (int i = 0; i < this->output()->number(); ++i)
    {
        double lambdaR = 0.0;
        for (int j = 0; j < this->input()->number(); ++j)
        {
            if (this->relation()->at(j).at(i))
            {
                lambdaR += lambdaS[j];
            }
        }
        double QR = 1.0 - PR[i];
        double muR = lambdaR * PR[i] / QR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR[i]);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

double GOMarkovOperator13A::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    QVector<double> PS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        PS.push_back(input[i]);
    }
    double PR = 1.0;
    for (int j = 0; j < this->input()->number(); ++j)
    {
        if (this->relation()->at(j).at(index))
        {
            PR *= PS[j];
        }
    }
    return PR;
}
