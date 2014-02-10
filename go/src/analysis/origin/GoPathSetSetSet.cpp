#include <cstdio>
#include "GoPathSetSetSet.h"
#include "GoPathSetSet.h"
#include "GoPathSet.h"
#include "GoOperator.h"
#include "GoMarkovStatus.h"
#include "GoMarkovOperator.h"
#include "GoMarkovOperator21.h"
#include "GoMarkovOperatorFactory.h"

GoPathSetSetSet::GoPathSetSetSet()
{
    this->_count = 0;
    this->_isCut = true;
}

GoPathSetSetSet::~GoPathSetSetSet()
{
    this->_list.clear();
    this->_endList.clear();
}

void GoPathSetSetSet::setIsCut(bool value)
{
    this->_isCut = value;
}

bool GoPathSetSetSet::isCut() const
{
    return this->_isCut;
}

void GoPathSetSetSet::add(GoOperator *endOperator, GoPathSet* path, int outputIndex, int vectorIndex)
{
    End end;
    end.op = endOperator;
    end.outputIndex = outputIndex;
    end.vectorIndex = vectorIndex;
    int index = -1;
    for (int i = 0; i < this->_endList.size(); ++i)
    {
        if (this->_endList[i] == end)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        index = this->_endList.size();
        this->_endList.push_back(end);
        this->_list.push_back(new GoPathSetSet());
    }
    bool flag = true;
    for (int i = 0; i < this->_list[index]->list().size(); ++i)
    {
        if (path->isContain(this->_list[index]->list().at(i)))
        {
            flag = false;
            break;
        }
    }
    if (flag)
    {
        this->_list[index]->add(path);
    }
}

QVector<GoPathSetSet *>& GoPathSetSetSet::list()
{
    return this->_list;
}


QVector<GoPathSetSetSet::End> GoPathSetSetSet::endList() const
{
    return this->_endList;
}

void GoPathSetSetSet::sort()
{
    for (int i = 0; i < this->_list.size(); ++i)
    {
        this->_list[i]->sort();
    }
    for (int i = 0; i < this->_endList.size(); ++i)
    {
        for (int j = i + 1; j < this->_endList.size(); ++j)
        {
            if (this->_endList[i] > this->_endList[j])
            {
                End temp1 = this->_endList[i];
                this->_endList[i] = this->_endList[j];
                this->_endList[j] = temp1;
                GoPathSetSet *temp2 = this->_list[i];
                this->_list[i] = this->_list[j];
                this->_list[j] = temp2;
            }
        }
    }
}

double GoPathSetSetSet::totalMarkovProbability(GoOperator *op) const
{
    for (int i = 0; i < this->_endList.size(); ++i)
    {
        if (this->_endList.at(i).op->realID() == op->realID())
        {
            return this->_list[i]->totalMarkovProbability();
        }
    }
    return 10.0;
}

double GoPathSetSetSet::totalMarkovProbability(int index) const
{
    if (index >= 0 && index < this->_list.size())
    {
        return this->_list[index]->totalMarkovProbability();
    }
    return 0.0;
}

double GoPathSetSetSet::totalMarkovProbability(int index, int count)
{
    double res = 0.0;
    for (int j = 0; j < this->list()[index]->list().size(); ++j)
    {
        double temp = 1.0;
        for (int k = 0; k < this->list()[index]->list()[j]->list().size(); ++k)
        {
            if (this->isCut())
            {
                temp *= 1.0 - this->_probabilities[this->list()[index]->list()[j]->list()[k]][count];
            }
            else
            {
                temp *= this->_probabilities[this->list()[index]->list()[j]->list()[k]][count];
            }
        }
        res += temp;
    }
    if (this->isCut())
    {
        res = 1.0 - res;
    }
    return res;
}

bool operator ==(const GoPathSetSetSet::End &a, const GoPathSetSetSet::End &b)
{
    return a.op == b.op && a.outputIndex == b.outputIndex && a.vectorIndex == b.vectorIndex;
}

bool operator <(const GoPathSetSetSet::End &a, const GoPathSetSetSet::End &b)
{
    if (a.op->id() == b.op->id())
    {
        if (a.outputIndex == b.outputIndex)
        {
            return a.vectorIndex < b.vectorIndex;
        }
        return a.outputIndex < b.outputIndex;
    }
    return a.op->id() < b.op->id();
}

bool operator >(const GoPathSetSetSet::End &a, const GoPathSetSetSet::End &b)
{
    if (a.op->id() == b.op->id())
    {
        if (a.outputIndex == b.outputIndex)
        {
            return a.vectorIndex > b.vectorIndex;
        }
        return a.outputIndex > b.outputIndex;
    }
    return a.op->id() > b.op->id();
}

void GoPathSetSetSet::setInterval(double interval)
{
    this->_interval = interval;
}

double GoPathSetSetSet::interval() const
{
    return this->_interval;
}

void GoPathSetSetSet::setCount(int count)
{
    this->_count = count;
}

int GoPathSetSetSet::count() const
{
    return this->_count;
}

void GoPathSetSetSet::initCalculation()
{
    this->_operators.clear();
    for (int i = 0; i < this->_list.size(); ++i)
    {
        QSet<GoOperator*> set = this->_list[i]->operatorSet();
        for (auto j = set.begin(); j != set.end(); ++j)
        {
            this->_operators.insert(*j);
        }
    }
    for (auto i = this->_operators.begin(); i != this->_operators.end(); ++i)
    {
        ((GoMarkovOperator*)(*i))->initCalculation(this->_interval);
    }
}

void GoPathSetSetSet::prepareNextCalculation(int count)
{
    for (auto i = this->_operators.begin(); i != this->_operators.end(); ++i)
    {
        ((GoMarkovOperator*)(*i))->prepareNextCalculation(count, count * this->_interval);
    }
}

void GoPathSetSetSet::finishCalculation()
{
    for (auto i = this->_operators.begin(); i != this->_operators.end(); ++i)
    {
        ((GoMarkovOperator*)(*i))->finishCalculation();
        ((GoMarkovOperator*)(*i))->initInfinityMarkovStatus();
    }
}

void GoPathSetSetSet::calcWithTime()
{
    if (this->count() == 0)
    {
        return;
    }
    this->_probabilities.clear();
    this->initCalculation();
    for (int i = 0; i < this->_count; ++i)
    {
        for (auto j = this->_operators.begin(); j != this->_operators.end(); ++j)
        {
            ((GoMarkovOperator*)(*j))->initMarkovStatus(i * this->_interval);
            if (((GoMarkovOperator*)(*j))->type() == GoMarkovOperatorFactory::Operator_Type_21)
            {
                this->_probabilities[*j].push_back(((GoMarkovOperator21*)(*j))->savedProbabilites()[i]);
            }
            else
            {
                this->_probabilities[*j].push_back(((GoMarkovOperator*)(*j))->markovStatus()->probabilityNormal().getValue(0));
            }
        }
        this->prepareNextCalculation(i);
    }
    this->finishCalculation();
}

double GoPathSetSetSet::getProbability(int count, GoPathSet *path)
{
    double res = 1.0;
    for (int i = 0; i < path->list().size(); ++i)
    {
        if (this->isCut())
        {
            res = res * (1.0 - this->_probabilities[path->list()[i]][count]);
        }
        else
        {
            res = res * this->_probabilities[path->list()[i]][count];
        }
    }
    return res;
}

double GoPathSetSetSet::getImportance(int count, GoPathSet *path, GoOperator* end)
{
    double probability = this->getProbability(count, path);
    double total = 0.0;
    for (int i = 0; i < this->_endList.size(); ++i)
    {
        if (this->_endList[i].op == end)
        {
            for (int j = 0; j < this->_list[i]->list().size(); ++j)
            {
                total += this->getProbability(count, this->_list[i]->list()[j]);
            }
            break;
        }
    }
    return probability / total;
}

QMap<GoOperator*, QVector<double>>& GoPathSetSetSet::probabilities()
{
    return this->_probabilities;
}
