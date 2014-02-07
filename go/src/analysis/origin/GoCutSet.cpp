#include <QObject>
#include "GoCutSet.h"
#include "GoStatus.h"
#include "GoOperator.h"
#include "GoMarkovOperator.h"
#include "GoMarkovStatus.h"

GoCutSet::GoCutSet() : GoPathSet()
{
}

GoCutSet* GoCutSet::copy()
{
    GoCutSet *cut = new GoCutSet();
    for (int i = 0; i < this->_list.size(); ++i)
    {
        cut->add(this->_list[i]);
    }
    cut->setTotalProbablity(this->totalProbablity());
    return cut;
}

double GoCutSet::toProbability() const
{
    double value = 1.0;
    for (int i = 0; i < this->_list.size(); ++i)
    {
        value = value * (1.0 - this->_list[i]->status()->probability(1));
    }
    return value;
}

double GoCutSet::toMarkovProbability() const
{
    DoubleVector value = 1.0;
    for (int i = 0; i < this->_list.size(); ++i)
    {
        GoMarkovOperator* op = (GoMarkovOperator*)this->_list[i];
        op->initMarkovStatus(1e10);
        value = value * op->markovStatus()->probabilityBreakdown();
    }
    return value.getValue(0);
}

QString GoCutSet::getProbabilityName() const
{
    return QObject::tr("Cut Failure Probablity");
}
