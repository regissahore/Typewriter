#include <qmath.h>
#include "GoMarkovOperator9b.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator9B::GoMarkovOperator9B() : GoMarkovOperator9()
{
    this->input()->setNumber(2);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator9B::~GoMarkovOperator9B()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
