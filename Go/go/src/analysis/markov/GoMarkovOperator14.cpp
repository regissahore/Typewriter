#include <qmath.h>
#include "GoMarkovOperator14.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator14::GoMarkovOperator14() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator14::~GoMarkovOperator14()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
