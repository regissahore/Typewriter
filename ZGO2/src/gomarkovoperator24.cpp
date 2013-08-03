#include <qmath.h>
#include "gomarkovoperator24.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator24::GOMarkovOperator24() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator24::~GOMarkovOperator24()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
