#include "gomarkovoperator9a.h"
#include "gomarkovstatus.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "goparameter.h"

GOMarkovOperator9A::GOMarkovOperator9A() : GOMarkovOperator9()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator9A::~GOMarkovOperator9A()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
