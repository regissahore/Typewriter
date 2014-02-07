#include "GoPathSetSetSet.h"
#include "GoPathSetSet.h"
#include "GoPathSet.h"
#include "GoOperator.h"

GoPathSetSetSet::GoPathSetSetSet()
{
}

GoPathSetSetSet::~GoPathSetSetSet()
{
    this->_list.clear();
    this->_endList.clear();
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

QVector<GoPathSetSet*> GoPathSetSetSet::list() const
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
