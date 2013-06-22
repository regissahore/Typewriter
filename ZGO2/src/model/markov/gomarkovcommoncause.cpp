#include "gomarkovcommoncause.h"

GOMarkovCommonCause::GOMarkovCommonCause() : DomItem()
{
}

GOMarkovCommonCause::~GOMarkovCommonCause()
{
}

QVector<GOMarkovOperator *> *GOMarkovCommonCause::operators() const
{
    return this->_operators;
}

double GOMarkovCommonCause::commonCause() const
{
    return this->_commonCause;
}

void GOMarkovCommonCause::setCommonCause(double value)
{
    this->_commonCause = value;
}
