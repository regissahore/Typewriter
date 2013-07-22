#include <qmath.h>
#include "gomarkovoperator22.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator22::GOMarkovOperator22() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator22::~GOMarkovOperator22()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
