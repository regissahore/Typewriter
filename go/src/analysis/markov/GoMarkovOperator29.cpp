#include <qmath.h>
#include "GoMarkovOperator29.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator29::GoMarkovOperator29() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator29::~GoMarkovOperator29()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
