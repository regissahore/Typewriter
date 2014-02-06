#include "GoStatus.h"

GoStatus::GoStatus()
{
    this->setNumber(3);
    this->_probability[1] = 1.0;
}

GoStatus::~GoStatus()
{
    this->_probability.clear();
    this->_description.clear();
}

int GoStatus::number() const
{
    return this->_probability.size();
}

void GoStatus::setNumber(int number)
{
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

double GoStatus::probability(int index) const
{
    if (index >= 0 && index < this->_probability.size())
    {
        return this->_probability[index];
    }
    return 0.0;
}

void GoStatus::setProbability(int index, double value)
{
    if (index >= 0 && index < this->_probability.size())
    {
        this->_probability[index] = value;
    }
}

QString GoStatus::description(int index) const
{
    if (index >= 0 && index < this->_description.size())
    {
        return this->_description[index];
    }
    return "";
}

void GoStatus::setDescription(int index, const QString value)
{
    if (index >= 0 && index < this->_description.size())
    {
        this->_description[index] = value;
    }
}

void GoStatus::save(QDomDocument &document, QDomElement &root)
{
    QDomElement statusRoot = document.createElement("status");
    for (int i = 0; i < this->number(); ++i)
    {
        QDomElement element = document.createElement(QString("status_%1").arg(i));
        element.setAttribute("probability", this->probability(i));
        element.setAttribute("description", this->description(i));
        statusRoot.appendChild(element);
    }
    root.appendChild(statusRoot);
}

bool GoStatus::tryOpen(QDomElement &root)
{
    if (root.tagName() != "status")
    {
        return false;
    }
    this->_probability.clear();
    this->_description.clear();
    for (auto element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        this->_probability.push_back(element.attribute("probability").toDouble());
        this->_description.push_back(element.attribute("description"));
    }
    return true;
}
