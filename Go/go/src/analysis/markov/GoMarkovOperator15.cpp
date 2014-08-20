#include <qmath.h>
#include "GoMarkovOperator15.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator15::GoMarkovOperator15() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator15::~GoMarkovOperator15()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
