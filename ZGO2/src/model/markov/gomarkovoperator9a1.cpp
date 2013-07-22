#include <qmath.h>
#include "gomarkovoperator9a1.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator9A1::GOMarkovOperator9A1() : GOMarkovOperator9A()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator9A1::~GOMarkovOperator9A1()
{
    this->GOMarkovOperator9A::~GOMarkovOperator9A();
}
