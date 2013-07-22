#include <qmath.h>
#include "gomarkovoperator18.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator18::GOMarkovOperator18() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator18::~GOMarkovOperator18()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}
