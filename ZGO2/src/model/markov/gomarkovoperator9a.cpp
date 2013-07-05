#include "gomarkovoperator9a.h"
#include "gomarkovstatus.h"

GOMarkovOperator9A::GOMarkovOperator9A() : GOMarkovOperator()
{
    this->_feedbackStatus = new GOMarkovStatus();
}

GOMarkovOperator9A::~GOMarkovOperator9A()
{
    this->GOMarkovOperator::~GOMarkovOperator();
    delete this->_feedbackStatus;
}

GOMarkovStatus* GOMarkovOperator9A::markovFeedbackStatus() const
{
    return this->_feedbackStatus;
}
