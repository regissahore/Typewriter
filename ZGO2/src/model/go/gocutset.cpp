#include "gocutset.h"
#include "gostatus.h"
#include "gooperator.h"

GOCutSet::GOCutSet() : GOPathSet()
{
}

GOPathSet* GOCutSet::copy()
{
    GOCutSet *cut = new GOCutSet();
    for (int i = 0; i < this->_list.size(); ++i)
    {
        cut->add(this->_list[i]);
    }
    return cut;
}

QString GOCutSet::toProbabilityString()
{
    double value = 1.0;
    for (int i = 0; i < this->_list.size(); ++i)
    {
        value = value * this->_list[i]->status()->probability(this->_list[i]->status()->number() - 1);
    }
    return QString("%1").arg(value);
}
