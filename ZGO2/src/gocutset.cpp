#include <QObject>
#include "gocutset.h"
#include "gostatus.h"
#include "gooperator.h"
#include "gomarkovoperator.h"
#include "gomarkovstatus.h"

GOCutSet::GOCutSet() : GOPathSet()
{
}

GOCutSet* GOCutSet::copy()
{
    GOCutSet *cut = new GOCutSet();
    for (int i = 0; i < this->_list.size(); ++i)
    {
        cut->add(this->_list[i]);
    }
    cut->setTotalProbablity(this->totalProbablity());
    return cut;
}

double GOCutSet::toProbability() const
{
    double value = 1.0;
    for (int i = 0; i < this->_list.size(); ++i)
    {
        value = value * (1.0 - this->_list[i]->status()->probability(1));
    }
    return value;
}

double GOCutSet::toMarkovProbability() const
{
    double value = 1.0;
    for (int i = 0; i < this->_list.size(); ++i)
    {
        GOMarkovOperator* op = (GOMarkovOperator*)this->_list[i];
        op->initMarkovStatus(1e10);
        value = value * op->markovStatus()->probabilityBreakdown();
    }
    return value;
}

QString GOCutSet::getProbabilityName() const
{
    return QObject::tr("Cut Failure Probablity");
}
