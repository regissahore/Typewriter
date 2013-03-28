#include "gograph.h"
#include "gooperator.h"
#include "gosignal.h"
#include "gooperatorfactory.h"

GOGraph::GOGraph()
{
}

GOGraph::~GOGraph()
{
    this->_operator.clear();
    this->_signal.clear();
}

QVector<GOOperator*> GOGraph::getSource() const
{
    return this->_source;
}

QVector<GOOperator*> GOGraph::getOperator() const
{
    return this->_operator;
}

QVector<GOSignal*> GOGraph::getSignal() const
{
    return this->_signal;
}

void GOGraph::addOperator(GOOperator *op)
{
    if (op->type() == GOOperatorFactory::Operator_Type_4 ||
            op->type() == GOOperatorFactory::Operator_Type_5)
    {
        this->_source.push_back(op);
    }
    else
    {
        this->_operator.push_back(op);
    }
}

void GOGraph::addSignal(GOSignal *signal)
{
    this->_signal.push_back(signal);
}
