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
