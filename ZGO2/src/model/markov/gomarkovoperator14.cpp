#include <qmath.h>
#include "gomarkovoperator14.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator14::GOMarkovOperator14() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator14::~GOMarkovOperator14()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
