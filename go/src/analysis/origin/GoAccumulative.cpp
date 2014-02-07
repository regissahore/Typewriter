#include "GoAccumulative.h"

GoAccumulative::GoAccumulative()
{
}

GoAccumulative::~GoAccumulative()
{
    this->_accumulative.clear();
}

int GoAccumulative::number() const
{
    return this->_accumulative.size();
}

void GoAccumulative::setNumber(int number)
{
    if (number > this->_accumulative.size())
    {
        number -= this->_accumulative.size();
        while (number--)
        {
            this->_accumulative.push_back(0.0);
        }
    }
    else if (number < this->_accumulative.size())
    {
        number = this->_accumulative.size() - number;
        while (number--)
        {
            this->_accumulative.remove(this->_accumulative.size() - 1);
        }
    }
}

double GoAccumulative::accumulative(int index) const
{
    if (index >= 0 && index < this->_accumulative.size())
    {
        return this->_accumulative[index];
    }
    return -1.0;
}

double GoAccumulative::probability(int index) const
{
    if (index > 0 && index < this->_accumulative.size())
    {
        return this->_accumulative[index] - this->_accumulative[index - 1];
    }
    return 0.0;
}

void GoAccumulative::setAccumulative(int index, double value)
{
    if (index >= 0 && index < this->_accumulative.size())
    {
        this->_accumulative[index] = value;
    }
}

GoAccumulative* GoAccumulative::copy() const
{
    GoAccumulative* acc = new GoAccumulative();
    acc->setNumber(this->number());
    for (int i = 0; i < this->number(); ++i)
    {
        acc->setAccumulative(i, this->accumulative(i));
    }
    return acc;
}
