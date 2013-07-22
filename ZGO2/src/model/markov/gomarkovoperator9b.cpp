#include <qmath.h>
#include "gomarkovoperator9b.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator9B::GOMarkovOperator9B() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator9B::~GOMarkovOperator9B()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
