#include "GoParameter.h"

GoParameter::GoParameter()
{
}

GoParameter::~GoParameter()
{
    this->_parameter.clear();
}

int GoParameter::number() const
{
    return this->_parameter.size();
}

void GoParameter::setNumber(int number)
{
    if (number > this->_parameter.size())
    {
        number -= this->_parameter.size();
        while (number--)
        {
            this->_parameter.push_back(number);
        }
    }
    else
    {
        number = this->_parameter.size() - number;
        while (number--)
        {
            this->_parameter.pop_back();
        }
    }
}

double GoParameter::parameter(const int index) const
{
    if (index >= 0 && index < this->_parameter.size())
    {
        return this->_parameter.at(index);
    }
    return 0.0;
}

void GoParameter::setParameter(const int index, const double value)
{
    if (index >= 0 && index < this->_parameter.size())
    {
        this->_parameter[index] = value;
    }
}

void GoParameter::save(QDomDocument &document, QDomElement &root)
{
    if (this->_parameter.size() > 0)
    {
        QDomElement extensionRoot = document.createElement("parameter");
        for (int i = 0; i < this->_parameter.size(); ++i)
        {
            QDomElement element = document.createElement("p");
            element.setAttribute("value", this->_parameter[i]);
            extensionRoot.appendChild(element);
        }
        root.appendChild(extensionRoot);
    }
}

bool GoParameter::tryOpen(QDomElement &root)
{
    if (!root.isNull())
    {
        if (root.tagName() != "parameter")
        {
            return false;
        }
        this->_parameter.clear();
        for (auto element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
        {
            this->_parameter.push_back(element.attribute("value").toDouble());
        }
    }
    return true;
}
