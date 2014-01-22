#include <qmath.h>
#include "GoMarkovOperator8.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator8::GoMarkovOperator8() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator8::~GoMarkovOperator8()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
