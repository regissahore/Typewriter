#include <qmath.h>
#include "gomarkovoperator3.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator3::GOMarkovOperator3() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator3::~GOMarkovOperator3()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
