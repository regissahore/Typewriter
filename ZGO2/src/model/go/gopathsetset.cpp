#include <QString>
#include "gopathsetset.h"
#include "gopathset.h"

GOPathSetSet::GOPathSetSet()
{
}

GOPathSetSet::~GOPathSetSet()
{
    for (int i = 0; i < this->_list.size(); ++i)
    {
        delete this->_list[i];
    }
    this->_list.clear();
}

void GOPathSetSet::add(GOPathSet* path)
{
    this->_list.push_back(path);
}

QVector<GOPathSet*> GOPathSetSet::list() const
{
    return this->_list;
}

void GOPathSetSet::sort()
{
    for (int i = this->_list.size() - 1; i >= 0; --i)
    {
        for (int j = 0; j < this->_list.size(); ++j)
        {
            if (i != j)
            {
                if (this->_list[i]->isContain(this->_list[j]))
                {
                    delete this->_list[i];
                    this->_list.remove(i);
                    break;
                }
            }
        }
    }
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
                GOPathSet* temp = this->_list[i];
                this->_list[i] = this->_list[j];
                this->_list[j] = temp;
            }
            else if (this->_list[i]->order() == this->_list[j]->order())
            {
                if (this->_list[i]->toCompareString() > this->_list[j]->toCompareString())
                {
                    GOPathSet* temp = this->_list[i];
                    this->_list[i] = this->_list[j];
                    this->_list[j] = temp;
                }
            }
        }
    }
}
