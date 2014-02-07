#include "GoMarkovOperator9a.h"
#include "GoMarkovStatus.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoParameter.h"

GoMarkovOperator9A::GoMarkovOperator9A() : GoMarkovOperator9()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator9A::~GoMarkovOperator9A()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator9A::calcQualitativeProbability()
{
    DoubleVector IS = this->getPrevQualitativeStatus();
    DoubleVector IC = this->qualitativeStatus();
    DoubleVector IR = IS * IC;
    this->_qualitativeOutput[0] = IR;
}
