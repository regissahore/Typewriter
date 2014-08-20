#include <qmath.h>
#include "GoMarkovOperator3.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator3::GoMarkovOperator3() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator3::~GoMarkovOperator3()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
