#include <qmath.h>
#include "gomarkovoperator29.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator29::GOMarkovOperator29() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator29::~GOMarkovOperator29()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
