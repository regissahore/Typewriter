#include <qmath.h>
#include "gomarkovoperator26.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator26::GOMarkovOperator26() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator26::~GOMarkovOperator26()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
