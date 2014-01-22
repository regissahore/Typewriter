#include <QString>
#include "gomarkovstatus.h"

GOMarkovStatus::GOMarkovStatus()
{
    this->setProbabilityNormal(1.0);
    this->setFrequencyBreakdown(0.0);
    this->setFrequencyRepair(1.0);
}

GOMarkovStatus::~GOMarkovStatus()
{
}

DoubleVector GOMarkovStatus::probabilityNormal() const
{
    return this->_probabilityNormal;
}

DoubleVector GOMarkovStatus::probabilityBreakdown() const
{
    return 1.0 - this->_probabilityNormal;
}

DoubleVector GOMarkovStatus::frequencyBreakdown() const
{
    return this->_frequencyBreakdown;
}

DoubleVector GOMarkovStatus::frequencyRepair() const
{
    return this->_frequencyRepair;
}

DoubleVector GOMarkovStatus::repairTime() const
{
    return 1.0 / this->_frequencyRepair;
}

void GOMarkovStatus::setProbabilityNormal(const DoubleVector &value)
{
    this->_probabilityNormal = value;
}

void GOMarkovStatus::setProbabilityBreakdown(const DoubleVector &value)
{
    this->_probabilityNormal = 1.0 - value;
}

void GOMarkovStatus::setFrequencyBreakdown(const DoubleVector &value)
{
    this->_frequencyBreakdown = value;
}

void GOMarkovStatus::setFrequencyRepair(const DoubleVector &value)
{
    this->_frequencyRepair = value;
}

void GOMarkovStatus::setRepairTime(const DoubleVector &value)
{
    this->setFrequencyRepair(1.0 / value);
}

void GOMarkovStatus::setProbabilityNormal(const int pos, const double value)
{
    this->_probabilityNormal.setValue(pos, value);
}

void GOMarkovStatus::setProbabilityBreakdown(const int pos, const double value)
{
    this->_probabilityNormal.setValue(pos, 1.0 - value);
}

void GOMarkovStatus::setFrequencyBreakdown(const int pos, const double value)
{
    this->_frequencyBreakdown.setValue(pos, value);
}

void GOMarkovStatus::setFrequencyRepair(const int pos, const double value)
{
    this->_frequencyRepair.setValue(pos, value);
}

void GOMarkovStatus::setRepairTime(const int pos, const double value)
{
    this->_frequencyRepair.setValue(pos, 1.0 / value);
}

void GOMarkovStatus::addHeadProbabilityNormal(const int pos, const int id, const int index)
{
    this->_probabilityNormal.addHead(pos, id, index);
}

void GOMarkovStatus::addHeadFrequencyBreakdown(const int pos, const int id, const int index)
{
    this->_frequencyBreakdown.addHead(pos, id, index);
}

void GOMarkovStatus::addHeadFrequencyRepair(const int pos, const int id, const int index)
{
    this->_frequencyRepair.addHead(pos, id, index);
}

GOMarkovStatus* GOMarkovStatus::copy() const
{
    GOMarkovStatus *status = new GOMarkovStatus();
    status->setProbabilityNormal(this->_probabilityNormal);
    status->setFrequencyBreakdown(this->_frequencyBreakdown);
    status->setFrequencyRepair(this->_frequencyRepair);
    return status;
}

void GOMarkovStatus::setVectorLength(const int len)
{
    this->_frequencyBreakdown.setLength(len);
    this->_frequencyRepair.setLength(len);
    this->_probabilityNormal.setLength(len);
}

void GOMarkovStatus::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("status");
    element.setAttribute("vector", this->_frequencyBreakdown.isVector());
    element.setAttribute("length", this->_frequencyBreakdown.length());
    if (this->_frequencyBreakdown.isVector())
    {
        for (int i = 0; i < this->_frequencyBreakdown.length(); ++i)
        {
            element.setAttribute(QString("breakdown_%1").arg(i), this->_frequencyBreakdown.getValue(i));
            element.setAttribute(QString("repair_%1").arg(i), this->_frequencyRepair.getValue(i));
        }
    }
    else
    {
        element.setAttribute("breakdown", this->_frequencyBreakdown.getValue(0));
        element.setAttribute("repair", this->_frequencyRepair.getValue(0));
    }
    root.appendChild(element);
}

bool GOMarkovStatus::tryOpen(QDomElement &root)
{
    if (root.tagName() != "status")
    {
        return false;
    }
    this->_frequencyBreakdown.setIsVector(root.attribute("vector", "0").toInt());
    this->_frequencyRepair.setIsVector(root.attribute("vector", "0").toInt());
    this->_frequencyBreakdown.setLength(root.attribute("length", "1").toInt());
    this->_frequencyRepair.setLength(root.attribute("length", "1").toInt());
    if (this->_frequencyBreakdown.isVector())
    {
        for (int i = 0; i < this->_frequencyBreakdown.length(); ++i)
        {
            this->_frequencyBreakdown.setValue(i, root.attribute(QString("breakdown_%1").arg(i)).toDouble());
            this->_frequencyRepair.setValue(i, root.attribute(QString("repair_%1").arg(i)).toDouble());
        }
    }
    this->setFrequencyBreakdown(root.attribute("breakdown").toDouble());
    this->setFrequencyRepair(root.attribute("repair").toDouble());
    return true;
}
