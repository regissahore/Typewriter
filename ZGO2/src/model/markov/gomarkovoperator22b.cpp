#include <qmath.h>
#include "gomarkovoperator22b.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator22B::GOMarkovOperator22B() : GOMarkovOperator22()
{
    this->input()->setNumber(2);
    this->subInput()->setNumber(1);
    this->output()->setNumber(3);
}

GOMarkovOperator22B::~GOMarkovOperator22B()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
