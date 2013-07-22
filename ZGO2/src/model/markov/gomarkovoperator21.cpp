#include <qmath.h>
#include "gomarkovoperator21.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator21::GOMarkovOperator21() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator21::~GOMarkovOperator21()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
