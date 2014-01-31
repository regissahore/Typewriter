#include <qmath.h>
#include "GoMarkovOperator9b.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator9B::GoMarkovOperator9B() : GoMarkovOperator9()
{
    this->input()->setNumber(2);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator9B::~GoMarkovOperator9B()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator9B::initCalculation(double interval)
{
    this->GoMarkovOperator9::initCalculation(interval);
    this->_lambdaS2Sum = 0.0;
    this->_muS2Sum = 0.0;
}

void GoMarkovOperator9B::prepareNextCalculation(int count, double time)
{
    this->GoMarkovOperator9::prepareNextCalculation(count, time);
    if (count > 0)
    {
        DoubleVector lambdaS2 = this->getPrevMarkovStatus(0)->frequencyBreakdown();
        DoubleVector muS2 = this->getPrevMarkovStatus(0)->frequencyRepair();
        if (isinf(lambdaS2.getValue(0)) || isnan(lambdaS2.getValue(0)))
        {
            this->_lambdaS2Sum = this->_lambdaS2Sum + this->lambdaS2;
        }
        else
        {
            this->_lambdaS2Sum = this->_lambdaS2Sum + lambdaS2;
            this->lambdaS2 = this->_lambdaS2Sum / count;
        }
        if (isinf(muS2.getValue(0)) || isnan(muS2.getValue(0)))
        {
            this->_muS2Sum = this->_muS2Sum + this->muS2;
        }
        else
        {
            this->_muS2Sum = this->_muS2Sum + muS2;
            this->muS2 = this->_muS2Sum / count;
        }
    }
}
