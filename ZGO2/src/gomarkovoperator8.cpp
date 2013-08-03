#include <qmath.h>
#include "gomarkovoperator8.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator8::GOMarkovOperator8() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator8::~GOMarkovOperator8()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
