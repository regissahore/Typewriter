#include <qmath.h>
#include "gomarkovoperator15.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator15::GOMarkovOperator15() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator15::~GOMarkovOperator15()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
