#include "gostatus.h"

GOStatus::GOStatus()
{
    this->setProbabilityNumber(2);
    this->setAccumulativeNumber(2);
}

/**
 * The number indicates the error status.
 * @return The error status.
 */
int GOStatus::probablityNumber() const
{
    return this->_probability.size() - 1;
}

void GOStatus::setProbabilityNumber(int number)
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

int GOStatus::accumulativeNumber() const
{
    return this->_accumulative.size() - 1;
}

void GOStatus::setAccumulativeNumber(int number)
{
    this->_accumulative.clear();
    for (int i = 0; i <= number; ++i)
    {
        this->_accumulative.push_back(0.0f);
    }
}

float GOStatus::accumulative(int index) const
{
    if (index >= 0 && index < this->_accumulative.size())
    {
        return this->_accumulative[index];
    }
    return 0.0f;
}

void GOStatus::setAccumulative(int index, const float value)
{
    if (index >= 0 && index < this->_accumulative.size())
    {
        this->_accumulative[index] = value;
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

void GOStatus::save(QDomDocument &document, QDomElement &root)
{
    QDomElement statusRoot = document.createElement("status");
    for (int i = 0; i <= this->probablityNumber(); ++i)
    {
        QDomElement element = document.createElement(QString("status_%1").arg(i));
        element.setAttribute("probability", this->probability(i));
        element.setAttribute("description", this->description(i));
        statusRoot.appendChild(element);
    }
    root.appendChild(statusRoot);
}

bool GOStatus::tryOpen(QDomElement &root)
{
    if (root.tagName() != "status")
    {
        return false;
    }
    this->_probability.clear();
    this->_description.clear();
    for (QDomElement element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        this->_probability.push_back(element.attribute("probability").toFloat());
        this->_description.push_back(element.attribute("description"));
    }
    return true;
}
