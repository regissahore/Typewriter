#include <qmath.h>
#include "GoMarkovOperator7.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator7::GoMarkovOperator7() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator7::~GoMarkovOperator7()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
