#include <qmath.h>
#include "GoMarkovOperator4.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator4::GoMarkovOperator4() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator4::~GoMarkovOperator4()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
