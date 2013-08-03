#include <qmath.h>
#include "gomarkovoperator27.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator27::GOMarkovOperator27() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator27::~GOMarkovOperator27()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
