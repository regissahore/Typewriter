#include <QString>
#include "gomarkovstatus.h"

GOMarkovStatus::GOMarkovStatus()
{
    this->setProbabilityNormal(BigDecimal::one());
    this->setFrequencyBreakdown(BigDecimal::one());
}

GOMarkovStatus::~GOMarkovStatus()
{
}

BigDecimal GOMarkovStatus::probabilityNormal() const
{
    return this->_probabilityNormal;
}

BigDecimal GOMarkovStatus::probabilityBreakdown() const
{
    return this->_probabilityBreakdown;
}

BigDecimal GOMarkovStatus::frequencyBreakdown() const
{
    return this->_frequencyBreakdown;
}

BigDecimal GOMarkovStatus::frequencyRepair() const
{
    return this->_frequencyRepair;
}

void GOMarkovStatus::setProbabilityNormal(QString value)
{
    this->setProbabilityNormal(BigDecimal::valueOf(value));
}

void GOMarkovStatus::setProbabilityBreakdown(QString value)
{
    this->setProbabilityBreakdown(BigDecimal::valueOf(value));
}

void GOMarkovStatus::setFrequencyBreakdown(QString value)
{
    this->setFrequencyBreakdown(BigDecimal::valueOf(value));
}

void GOMarkovStatus::setFrequencyRepair(QString value)
{
    this->setFrequencyRepair(BigDecimal::valueOf(value));
}

void GOMarkovStatus::setProbabilityNormal(BigDecimal value)
{
    this->_probabilityNormal = value;
    this->_probabilityBreakdown = BigDecimal::one() - value;
}

void GOMarkovStatus::setProbabilityBreakdown(BigDecimal value)
{
    this->_probabilityBreakdown = value;
    this->_probabilityNormal = BigDecimal::one() - value;
}

void GOMarkovStatus::setFrequencyBreakdown(BigDecimal value)
{
    this->_frequencyBreakdown = value;
    this->_frequencyRepair = this->_probabilityNormal * this->_frequencyBreakdown / this->_probabilityBreakdown;
}

void GOMarkovStatus::setFrequencyRepair(BigDecimal value)
{
    this->_frequencyRepair = value;
    this->_frequencyBreakdown = this->_probabilityBreakdown * this->_frequencyRepair / this->_probabilityNormal;
}

void GOMarkovStatus::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("status");
    element.setAttribute("probability_normal", this->_probabilityNormal.toString());
    element.setAttribute("frequency_breakdown", this->_frequencyBreakdown.toString());
    root.appendChild(element);
}

bool GOMarkovStatus::tryOpen(QDomElement &root)
{
    if (root.tagName() != "status")
    {
        return false;
    }
    this->setProbabilityNormal(root.attribute("probability_normal"));
    this->setFrequencyBreakdown(root.attribute("frequency_breakdown"));
    return true;
}
