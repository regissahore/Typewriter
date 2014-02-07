#include <qmath.h>
#include "GoMarkovOperator12.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator12::GoMarkovOperator12() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator12::~GoMarkovOperator12()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
