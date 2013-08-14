#include <QObject>
#include "gopathset.h"
#include "gooperator.h"
#include "gostatus.h"
#include "gomarkovoperator.h"
#include "gomarkovstatus.h"

GOPathSet::GOPathSet()
{
}

GOPathSet::~GOPathSet()
{
    this->_list.clear();
}

int GOPathSet::order() const
{
    return this->_list.size();
}

void GOPathSet::add(GOOperator *op)
{
    this->_list.push_back(op);
}

void GOPathSet::removeEnd()
{
    this->_list.pop_back();
}

QVector<GOOperator*> GOPathSet::list() const
{
    return this->_list;
}

void GOPathSet::sort()
{
    for (int i = 0; i < this->_list.size(); ++i)
    {
        for (int j = i + 1; j < this->_list.size(); ++j)
        {
            if (this->_list[i]->id() > this->_list[j]->id())
            {
                GOOperator *temp = this->_list[i];
                this->_list[i] = this->_list[j];
                this->_list[j] = temp;
            }
        }
    }
}

QString GOPathSet::toIdString()
{
    this->sort();
    QString str = "";
    for (int i = 0; i < this->_list.size(); ++i)
    {
        str += QString("%1 ").arg(this->_list[i]->id());
    }
    return str;
}

QString GOPathSet::toCompareString()
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

QString GOPathSet::toProbabilityString()
{
    double value = 1.0;
    for (int i = 0; i < this->_list.size(); ++i)
    {
        value = value * (1.0 - this->_list[i]->status()->probability(this->_list[i]->status()->number() - 1));
    }
    return QString("%1").arg(value);
}

QString GOPathSet::toMarkovProbabilityString()
{
    double value = 1.0;
    for (int i = 0; i < this->_list.size(); ++i)
    {
        GOMarkovOperator* op = (GOMarkovOperator*)this->_list[i];
        op->initMarkovStatus(1e10);
        value = value * op->markovStatus()->probabilityNormal();
    }
    return QString("%1").arg(value);
}

QString GOPathSet::toNameString()
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

QString GOPathSet::getProbabilityName() const
{
    return QObject::tr("Path Success Probablity");
}

GOPathSet* GOPathSet::copy()
{
    GOPathSet *path = new GOPathSet();
    for (int i = 0; i < this->_list.size(); ++i)
    {
        path->add(this->_list[i]);
    }
    return path;
}

bool GOPathSet::isContain(GOPathSet *set)
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
