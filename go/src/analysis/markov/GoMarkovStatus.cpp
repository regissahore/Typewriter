#include <QString>
#include "GoMarkovStatus.h"

GoMarkovStatus::GoMarkovStatus()
{
    this->setProbabilityNormal(1.0);
    this->setFrequencyBreakdown(0.0);
    this->setFrequencyRepair(1.0);
}

GoMarkovStatus::~GoMarkovStatus()
{
}

DoubleVector GoMarkovStatus::probabilityNormal() const
{
    return this->_probabilityNormal;
}

DoubleVector GoMarkovStatus::probabilityBreakdown() const
{
    return 1.0 - this->_probabilityNormal;
}

DoubleVector GoMarkovStatus::frequencyBreakdown() const
{
    return this->_frequencyBreakdown;
}

DoubleVector GoMarkovStatus::frequencyRepair() const
{
    return this->_frequencyRepair;
}

DoubleVector GoMarkovStatus::repairTime() const
{
    return 1.0 / this->_frequencyRepair;
}

void GoMarkovStatus::setProbabilityNormal(const DoubleVector &value)
{
    this->_probabilityNormal = value;
}

void GoMarkovStatus::setProbabilityBreakdown(const DoubleVector &value)
{
    this->_probabilityNormal = 1.0 - value;
}

void GoMarkovStatus::setFrequencyBreakdown(const DoubleVector &value)
{
    this->_frequencyBreakdown = value;
}

void GoMarkovStatus::setFrequencyRepair(const DoubleVector &value)
{
    this->_frequencyRepair = value;
}

void GoMarkovStatus::setRepairTime(const DoubleVector &value)
{
    this->setFrequencyRepair(1.0 / value);
}

void GoMarkovStatus::setProbabilityNormal(const int pos, const double value)
{
    this->_probabilityNormal.setValue(pos, value);
}

void GoMarkovStatus::setProbabilityBreakdown(const int pos, const double value)
{
    this->_probabilityNormal.setValue(pos, 1.0 - value);
}

void GoMarkovStatus::setFrequencyBreakdown(const int pos, const double value)
{
    this->_frequencyBreakdown.setValue(pos, value);
}

void GoMarkovStatus::setFrequencyRepair(const int pos, const double value)
{
    this->_frequencyRepair.setValue(pos, value);
}

void GoMarkovStatus::setRepairTime(const int pos, const double value)
{
    this->_frequencyRepair.setValue(pos, 1.0 / value);
}

void GoMarkovStatus::addHeadProbabilityNormal(const int pos, const int id, const int index)
{
    this->_probabilityNormal.addHead(pos, id, index);
}

void GoMarkovStatus::addHeadFrequencyBreakdown(const int pos, const int id, const int index)
{
    this->_frequencyBreakdown.addHead(pos, id, index);
}

void GoMarkovStatus::addHeadFrequencyRepair(const int pos, const int id, const int index)
{
    this->_frequencyRepair.addHead(pos, id, index);
}

GoMarkovStatus* GoMarkovStatus::copy() const
{
    GoMarkovStatus *status = new GoMarkovStatus();
    status->setProbabilityNormal(this->_probabilityNormal);
    status->setFrequencyBreakdown(this->_frequencyBreakdown);
    status->setFrequencyRepair(this->_frequencyRepair);
    return status;
}

void GoMarkovStatus::setVectorLength(const int len)
{
    this->_frequencyBreakdown.setLength(len);
    this->_frequencyRepair.setLength(len);
    this->_probabilityNormal.setLength(len);
}

void GoMarkovStatus::save(QDomDocument &document, QDomElement &root)
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

bool GoMarkovStatus::tryOpen(QDomElement &root)
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
