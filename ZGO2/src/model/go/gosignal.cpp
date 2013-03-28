#include "gosignal.h"
#include "gooperator.h"

GOSignal::GOSignal()
{
    this->_u = 0L;
    this->_v = 0L;
}

GOOperator *GOSignal::u() const
{
    return this->_u;
}

GOOperator *GOSignal::v() const
{
    return this->_v;
}

GOOperator *GOSignal::next(GOOperator *op) const
{
    if (this->_u == op)
    {
        return this->_v;
    }
    return this->_u;
}

void GOSignal::setU(GOOperator *u)
{
    this->_u = u;
}

void GOSignal::setV(GOOperator *v)
{
    this->_v = v;
}
