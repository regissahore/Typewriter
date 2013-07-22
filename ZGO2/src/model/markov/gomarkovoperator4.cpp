#include <qmath.h>
#include "gomarkovoperator4.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator4::GOMarkovOperator4() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator4::~GOMarkovOperator4()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
