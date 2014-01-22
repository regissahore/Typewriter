#include <qmath.h>
#include "gomarkovoperator12.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator12::GOMarkovOperator12() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator12::~GOMarkovOperator12()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
