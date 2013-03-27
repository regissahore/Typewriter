#include "gostatus.h"

GOStatus::GOStatus()
{
    this->setNumber(2);
}

/**
 * The number indicates the error status.
 * @return The error status.
 */
int GOStatus::number() const
{
    return this->_probability.size() - 1;
}

void GOStatus::setNumber(int number)
{
    ++ number;
    if (number > this->_probability.size())
    {
        number = number - this->_probability.size();
        while (number--)
        {
            this->_probability.push_back(0.0);
            this->_description.push_back("");
        }
    }
    else if (number < this->_probability.size())
    {
        number = this->_probability.size() - number;
        while (number--)
        {
            this->_probability.remove(this->_probability.size() - 1);
            this->_description.remove(this->_description.size() - 1);
        }
    }
}

float GOStatus::probability(int index) const
{
    if (index >= 0 && index < this->_probability.size())
    {
        return this->_probability[index];
    }
    return 0.0f;
}

void GOStatus::setProbability(int index, const float value)
{
    if (index >= 0 && index < this->_probability.size())
    {
        this->_probability[index] = value;
    }
}

QString GOStatus::description(int index) const
{
    if (index >= 0 && index < this->_description.size())
    {
        return this->_description[index];
    }
    return "";
}

void GOStatus::setDescription(int index, const QString value)
{
    if (index >= 0 && index < this->_description.size())
    {
        this->_description[index] = value;
    }
}
