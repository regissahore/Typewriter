#include <qmath.h>
#include "GoMarkovOperator25.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator25::GoMarkovOperator25() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator25::~GoMarkovOperator25()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}
