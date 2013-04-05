#include "gopathsetsetset.h"
#include "gopathsetset.h"
#include "gooperator.h"

GOPathSetSetSet::GOPathSetSetSet()
{
}

GOPathSetSetSet::~GOPathSetSetSet()
{
    this->_list.clear();
    this->_endList.clear();
}

void GOPathSetSetSet::add(GOOperator *end, GOPathSet* path)
{
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
        this->_list.push_back(new GOPathSetSet());
    }
    this->_list[index]->add(path);
}

QVector<GOPathSetSet*> GOPathSetSetSet::list() const
{
    return this->_list;
}


QVector<GOOperator*> GOPathSetSetSet::endList() const
{
    return this->_endList;
}

void GOPathSetSetSet::sort()
{
    for (int i = 0; i < this->_list.size(); ++i)
    {
        this->_list[i]->sort();
    }
    for (int i = 0; i < this->_endList.size(); ++i)
    {
        for (int j = i + 1; j < this->_endList.size(); ++j)
        {
            if (this->_endList[i]->id() > this->_endList[j]->id())
            {
                GOOperator *temp1 = this->_endList[i];
                this->_endList[i] = this->_endList[j];
                this->_endList[j] = temp1;
                GOPathSetSet *temp2 = this->_list[i];
                this->_list[i] = this->_list[j];
                this->_list[j] = temp2;
            }
        }
    }
}
