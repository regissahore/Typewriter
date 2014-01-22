#include <qmath.h>
#include "GoMarkovOperator27.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator27::GoMarkovOperator27() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator27::~GoMarkovOperator27()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
