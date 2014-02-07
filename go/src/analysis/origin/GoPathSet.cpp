#include <QObject>
#include "GoPathSet.h"
#include "GoOperator.h"
#include "GoStatus.h"
#include "GoMarkovOperator.h"
#include "GoMarkovStatus.h"

GoPathSet::GoPathSet()
{
}

GoPathSet::~GoPathSet()
{
    this->_list.clear();
}

int GoPathSet::order() const
{
    return this->_list.size();
}

void GoPathSet::add(GoOperator *op)
{
    this->_list.push_back(op);
}

void GoPathSet::removeEnd()
{
    this->_list.pop_back();
}

QVector<GoOperator*> GoPathSet::list() const
{
    return this->_list;
}

void GoPathSet::sort()
{
    for (int i = 0; i < this->_list.size(); ++i)
    {
        for (int j = i + 1; j < this->_list.size(); ++j)
        {
            if (this->_list[i]->id() > this->_list[j]->id())
            {
                GoOperator *temp = this->_list[i];
                this->_list[i] = this->_list[j];
                this->_list[j] = temp;
            }
        }
    }
}

QString GoPathSet::toIdString()
{
    this->sort();
    QString str = "";
    for (int i = 0; i < this->_list.size(); ++i)
    {
        str += QString("%1 ").arg(this->_list[i]->id());
    }
    return str;
}

QString GoPathSet::toCompareString()
{
    this->sort();
    QString str = "";
    for (int i = 0; i < this->_list.size(); ++i)
    {
        QString temp = QString("%1").arg(this->_list[i]->id());
        int number = 11 - temp.length();
        for (int j = 0; j < number; ++j)
        {
            str += " ";
        }
        str += temp;
    }
    return str;
}

double GoPathSet::toProbability() const
{
    double value = 1.0;
    for (int i = 0; i < this->_list.size(); ++i)
    {
        value = value * (1.0 - this->_list[i]->status()->probability(this->_list[i]->status()->number() - 1));
    }
    return value;
}

double GoPathSet::toMarkovProbability() const
{
    DoubleVector value = 1.0;
    for (int i = 0; i < this->_list.size(); ++i)
    {
        GoMarkovOperator* op = (GoMarkovOperator*)this->_list[i];
        op->initMarkovStatus(1e10);
        value = value * op->markovStatus()->probabilityNormal();
    }
    return value.getValue(0);
}

double GoPathSet::toImportance() const
{
    return this->toProbability() / this->totalProbablity();
}

double GoPathSet::toMarkovImportance() const
{
    return this->toMarkovProbability() / this->totalProbablity();
}

QString GoPathSet::toProbabilityString() const
{
    return QString::number(this->toProbability(), 'f', 10);
}

QString GoPathSet::toMarkovProbabilityString() const
{
    return QString::number(this->toMarkovProbability(), 'f', 10);
}

QString GoPathSet::toImportanceString() const
{
    return QString::number(this->toImportance(), 'f', 10);
}

QString GoPathSet::toMarkovImportanceString() const
{
    return QString::number(this->toMarkovImportance(), 'f', 10);
}

QString GoPathSet::toNameString()
{
    QString res;
    for (int i = 0; i < this->_list.size(); ++i)
    {
        if (i)
        {
            res += " ";
        }
        res += this->_list[i]->name();
    }
    return res;
}

QString GoPathSet::getProbabilityName() const
{
    return QObject::tr("Path Success Probablity");
}

GoPathSet* GoPathSet::copy()
{
    GoPathSet *path = new GoPathSet();
    for (int i = 0; i < this->_list.size(); ++i)
    {
        path->add(this->_list[i]);
    }
    path->setTotalProbablity(this->totalProbablity());
    return path;
}

bool GoPathSet::isContain(GoPathSet *set)
{
    if (this->order() <= set->order())
    {
        return false;
    }
    for (int i = 0; i < set->_list.size(); ++i)
    {
        bool flag = true;
        for (int j = 0; j < this->_list.size(); ++j)
        {
            if (set->_list[i] == this->_list[j])
            {
                flag = false;
            }
        }
        if (flag)
        {
            return false;
        }
    }
    return true;
}

double GoPathSet::totalProbablity() const
{
    return this->_totalProbability;
}

void GoPathSet::setTotalProbablity(const double value)
{
    this->_totalProbability = value;
}
