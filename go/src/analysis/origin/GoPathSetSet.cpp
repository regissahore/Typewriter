#include <cstdio>
#include <QString>
#include "GoPathSetSet.h"
#include "GoPathSet.h"

GoPathSetSet::GoPathSetSet()
{
}

GoPathSetSet::~GoPathSetSet()
{
    for (int i = 0; i < this->_list.size(); ++i)
    {
        delete this->_list[i];
    }
    this->_list.clear();
}

void GoPathSetSet::add(GoPathSet* path)
{
    this->_list.push_back(path);
}

QVector<GoPathSet*> GoPathSetSet::list() const
{
    return this->_list;
}

void GoPathSetSet::sort()
{
    for (int i = 0; i < this->_list.size(); ++i)
    {
        this->_list[i]->sort();
    }
    for (int i = 0; i < this->_list.size(); ++i)
    {
        for (int j = i + 1; j < this->_list.size(); ++j)
        {
            if (this->_list[i]->order() > this->_list[j]->order())
            {
                GoPathSet* temp = this->_list[i];
                this->_list[i] = this->_list[j];
                this->_list[j] = temp;
            }
            else if (this->_list[i]->order() == this->_list[j]->order())
            {
                if (this->_list[i]->toCompareString() > this->_list[j]->toCompareString())
                {
                    GoPathSet* temp = this->_list[i];
                    this->_list[i] = this->_list[j];
                    this->_list[j] = temp;
                }
            }
        }
    }
}

double GoPathSetSet::totalMarkovProbability() const
{
    double res = 0.0;
    for (int i = 0; i < this->_list.size(); ++i)
    {
        res += this->_list[i]->toMarkovProbability();
    }
    return res;
}
