#include "goaccumulative.h"

GOAccumulative::GOAccumulative()
{
}

int GOAccumulative::number() const
{
    return this->_accumulative.size();
}

void GOAccumulative::setNumber(int number)
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

double GOAccumulative::accumulative(int index) const
{
    if (index >= 0 && index < this->_accumulative.size())
    {
        return this->_accumulative[index];
    }
    return -1.0;
}

void GOAccumulative::setAccumulative(int index, double value)
{
    if (index >= 0 && index < this->_accumulative.size())
    {
        this->_accumulative[index] = value;
    }
}

/**
 * Return a numeric copy of the accumulative probability.
 * @return The numeric copy.
 */
GOAccumulative* GOAccumulative::copy() const
{
    GOAccumulative* acc = new GOAccumulative();
    acc->setNumber(this->number());
    for (int i = 0; i < this->number(); ++i)
    {
        acc->setAccumulative(i, this->accumulative(i));
    }
    return acc;
}
