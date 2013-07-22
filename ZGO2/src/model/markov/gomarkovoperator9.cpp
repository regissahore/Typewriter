#include <qmath.h>
#include "gomarkovoperator9.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator9::GOMarkovOperator9() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator9::~GOMarkovOperator9()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
