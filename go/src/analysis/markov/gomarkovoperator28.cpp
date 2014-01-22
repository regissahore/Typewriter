#include <qmath.h>
#include "GoMarkovOperator28.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator28::GoMarkovOperator28() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator28::~GoMarkovOperator28()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

