#include <qmath.h>
#include "GoMarkovOperator24.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator24::GoMarkovOperator24() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator24::~GoMarkovOperator24()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
