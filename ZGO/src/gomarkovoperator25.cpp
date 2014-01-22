#include <qmath.h>
#include "gomarkovoperator25.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator25::GOMarkovOperator25() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator25::~GOMarkovOperator25()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
