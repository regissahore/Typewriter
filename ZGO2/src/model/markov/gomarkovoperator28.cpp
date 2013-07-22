#include <qmath.h>
#include "gomarkovoperator28.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator28::GOMarkovOperator28() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator28::~GOMarkovOperator28()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

