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
    QVector<double> PS;
    QVector<double> muS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *status = this->getPrevMarkovStatus(i);
        PS.push_back(status->probabilityNormal());
        muS.push_back(status->frequencyRepair());
    }
    for (int i = 0; i < this->output()->number(); ++i)
    {
        double PR = 0.0;
        double muR = 0.0;
        for (int j = 0; j < this->input()->number(); ++j)
        {
            if (this->relation()->at(j).at(i))
            {
                PR += PS[j];
                muR += muS[j];
            }
        }
        double QR = 1.0 - PR;
        double lambdaR = muR * QR / PR;
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

void GOMarkovOperator13B::calcCommonOutputMarkovStatus(QVector<double> PR)
{
    QVector<double> muS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *status = this->getPrevMarkovStatus(i);
        muS.push_back(status->frequencyRepair());
    }
    for (int i = 0; i < this->output()->number(); ++i)
    {
        double muR = 0.0;
        for (int j = 0; j < this->input()->number(); ++j)
        {
            if (this->relation()->at(j).at(i))
            {
                muR += muS[j];
            }
        }
        double QR = 1.0 - PR[i];
        double lambdaR = muR * QR / PR[i];
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR[i]);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

double GOMarkovOperator13B::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    QVector<double> PS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        PS.push_back(input[i]);
    }
    double PR = 0.0;
    for (int j = 0; j < this->input()->number(); ++j)
    {
        if (this->relation()->at(j).at(index))
        {
            PR += PS[j];
        }
    }
    return PR;
}
