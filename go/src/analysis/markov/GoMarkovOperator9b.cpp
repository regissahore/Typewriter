#include <algorithm>
#include <qmath.h>
#include "GoMarkovOperator9b.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"
using namespace std;

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

void GoMarkovOperator9B::calcQualitativeProbability()
{
    DoubleVector IS1 = this->getPrevQualitativeStatus(0);
    DoubleVector IS2 = this->getPrevQualitativeStatus(1);
    DoubleVector IC = this->qualitativeStatus();
    DoubleVector IR = IS1 * IS2 * IC;
    this->_qualitativeOutput[0] = IR;
}

void GoMarkovOperator9B::initCalculation(double interval)
{
    this->GoMarkovOperator9::initCalculation(interval);
    this->_lambdaS2Sum = 0.0;
    this->_muS2Sum = 0.0;
    this->_sumCount2 = 0.0;
}

void GoMarkovOperator9B::prepareSum()
{
    this->GoMarkovOperator9::prepareSum();
    if (this->_currentCount > this->_sumCount2)
    {
        DoubleVector lambdaS2 = this->getPrevMarkovStatus(1)->frequencyBreakdown();
        DoubleVector muS2 = this->getPrevMarkovStatus(1)->frequencyRepair();
        if (std::isinf(lambdaS2.getValue(0)) || std::isnan(lambdaS2.getValue(0)))
        {
            this->_lambdaS2Sum = this->_lambdaS2Sum + this->lambdaS2;
        }
        else
        {
            this->_lambdaS2Sum = this->_lambdaS2Sum + lambdaS2;
            this->lambdaS2 = this->_lambdaS2Sum / this->_currentCount;
        }
        if (std::isinf(muS2.getValue(0)) || std::isnan(muS2.getValue(0)))
        {
            this->_muS2Sum = this->_muS2Sum + this->muS2;
        }
        else
        {
            this->_muS2Sum = this->_muS2Sum + muS2;
            this->muS2 = this->_muS2Sum / this->_currentCount;
        }
        ++this->_sumCount2;
    }
}
