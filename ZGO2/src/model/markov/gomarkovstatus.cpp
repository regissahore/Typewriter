#include <QString>
#include "gomarkovstatus.h"

GOMarkovStatus::GOMarkovStatus()
{
    this->setFrequencyBreakdown(0.0);
    this->setFrequencyRepair(1.0);
}

GOMarkovStatus::~GOMarkovStatus()
{
}

double GOMarkovStatus::probabilityNormal() const
{
    return this->_probabilityNormal;
}

double GOMarkovStatus::probabilityBreakdown() const
{
    return this->_probabilityBreakdown;
}

double GOMarkovStatus::frequencyBreakdown() const
{
    return this->_frequencyBreakdown;
}

double GOMarkovStatus::frequencyRepair() const
{
    return this->_frequencyRepair;
}

void GOMarkovStatus::setProbabilityNormal(double value)
{
    this->_probabilityNormal = value;
    this->_probabilityBreakdown = 1.0 - value;
}

void GOMarkovStatus::setProbabilityBreakdown(double value)
{
    this->_probabilityBreakdown = value;
    this->_probabilityNormal = 1.0 - value;
}

void GOMarkovStatus::setFrequencyBreakdown(double value)
{
    this->_frequencyBreakdown = value;
}

void GOMarkovStatus::setFrequencyRepair(double value)
{
    this->_frequencyRepair = value;
}

void GOMarkovStatus::setRepairTime(double value)
{
    this->setFrequencyRepair(1.0 / value);
}

void GOMarkovStatus::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("status");
    element.setAttribute("breakdown", this->_frequencyBreakdown);
    element.setAttribute("repair", this->_frequencyRepair);
    root.appendChild(element);
}

bool GOMarkovStatus::tryOpen(QDomElement &root)
{
    if (root.tagName() != "status")
    {
        return false;
    }
    this->setFrequencyBreakdown(root.attribute("breakdown").toDouble());
    this->setFrequencyRepair(root.attribute("repair").toDouble());
    return true;
}
