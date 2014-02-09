#include <QObject>
#include "GoCutSet.h"
#include "GoStatus.h"
#include "GoOperator.h"
#include "GoMarkovOperator.h"
#include "GoMarkovOperator21.h"
#include "GoMarkovStatus.h"
#include "GoMarkovOperatorFactory.h"
#include "RungeKuttaBreakdown2.h"
#include "RungeKuttaBreakdown3.h"
#include "RungeKuttaBreakdown4.h"

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
    cut->setTotalProbablity(this->_totalProbability);
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
        if (op->type() == GoMarkovOperatorFactory::Operator_Type_21)
        {
            GoMarkovOperator21* op21 = (GoMarkovOperator21*)op;
            value = value * op21->cutProbability();
        }
        else
        {
            if (op->breakdownNum() == 1)
            {
                value = value * op->markovStatus()->probabilityBreakdown();
            }
            else if (op->breakdownNum() == 2)
            {
                value = value * (1.0 - op->rkBreakdown2()->getInf(0));
            }
            else if (op->breakdownNum() == 3)
            {
                value = value * (1.0 - op->rkBreakdown3()->getInf(0));
            }
            else if (op->breakdownNum() == 4)
            {
                value = value * (1.0 - op->rkBreakdown4()->getInf(0));
            }
        }
    }
    return value.getValue(0);
}

QString GoCutSet::getProbabilityName() const
{
    return QObject::tr("Cut Failure Probablity");
}
