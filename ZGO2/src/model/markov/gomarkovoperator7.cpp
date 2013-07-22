#include <qmath.h>
#include "gomarkovoperator7.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator7::GOMarkovOperator7() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator7::~GOMarkovOperator7()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
