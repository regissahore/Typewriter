#include "GoSignal.h"
#include "GoOperator.h"

GoSignal::GoSignal()
{
    this->_u = nullptr;
    this->_v = nullptr;
    this->setIsGlobalFeedback(false);
}

GoSignal::~GoSignal()
{
}

GoOperator *GoSignal::u() const
{
    return this->_u;
}

GoOperator *GoSignal::v() const
{
    return this->_v;
}

GoOperator *GoSignal::next(GoOperator *op) const
{
    if (this->_u == op)
    {
        return this->_v;
    }
    return this->_u;
}

void GoSignal::setU(GoOperator *u)
{
    this->_u = u;
}

void GoSignal::setV(GoOperator *v)
{
    this->_v = v;
}

bool GoSignal::isGlobalFeedback() const
{
    return this->_isGlobalFeedback;
}

void GoSignal::setIsGlobalFeedback(const bool value)
{
    this->_isGlobalFeedback = value;
}
