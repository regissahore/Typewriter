#include "GoMarkovOperator13a.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoMarkovStatus.h"

GoMarkovOperator13A::GoMarkovOperator13A() : GoMarkovOperator13()
{
}

GoMarkovOperator13A::~GoMarkovOperator13A()
{
    this->GoMarkovOperator13::~GoMarkovOperator13();
}

void GoMarkovOperator13A::calcQualitativeProbability()
{
    QVector<DoubleVector> IS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        IS.push_back(this->getPrevQualitativeStatus(i));
    }
    for (int i = 0; i < this->output()->number(); ++i)
    {
        DoubleVector IR = 1.0;
        for (int j = 0; j < this->input()->number(); ++j)
        {
            if (this->relation()->at(j).at(i))
            {
                IR = IR * IS[j];
            }
        }
        this->_qualitativeOutput[i] = IR;
    }
}

void GoMarkovOperator13A::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    QVector<DoubleVector> PS;
    QVector<DoubleVector> lambdaS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *status = this->getPrevMarkovStatus(i);
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

void GoMarkovOperator13A::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    QVector<DoubleVector> lambdaS;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *status = this->getPrevMarkovStatus(i);
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

DoubleVector GoMarkovOperator13A::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
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
