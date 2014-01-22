#include <qmath.h>
#include "GoMarkovOperator26.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator26::GoMarkovOperator26() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator26::~GoMarkovOperator26()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
