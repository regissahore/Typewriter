#include "GoMarkovEquivalentSeries.h"
#include "GoMarkovStatus.h"
#include "GoMarkovOperator.h"

GoMarkovEquivalentSeries::GoMarkovEquivalentSeries() : GoMarkovEquivalent()
{
}

GoMarkovStatus GoMarkovEquivalentSeries::getEquivalentStatus()
{
    GoMarkovStatus status;
    if (this->I() == 1)
    {
        DoubleVector lamda = 0.0;
        DoubleVector lamdaFracSum = 0.0;
        for (int i = 0; i < this->_operators->size(); ++i)
        {
            lamda = lamda + this->_operators->at(i)->markovStatus1()->frequencyBreakdown();
            lamdaFracSum = lamdaFracSum + this->_operators->at(i)->markovStatus1()->frequencyBreakdown() / this->_operators->at(i)->markovStatus1()->frequencyRepair();
        }
        DoubleVector miu = lamda / lamdaFracSum;
        status.setFrequencyBreakdown(lamda);
        status.setFrequencyRepair(miu);
    }
    else
    {
        DoubleVector lamda = 0.0;
        DoubleVector p1 = 1.0;
        for (int i = 0; i < this->_operators->size(); ++i)
        {
            lamda = lamda + this->_operators->at(i)->markovStatus1()->frequencyBreakdown();
            p1 = p1 * this->_operators->at(i)->markovStatus1()->probabilityNormal();
        }
        DoubleVector miu = lamda * p1 / (1.0 - p1);
        status.setFrequencyBreakdown(lamda);
        status.setFrequencyRepair(miu);
    }
    return status;
}

void GoMarkovEquivalentSeries::save(QDomDocument &document, QDomElement &root)
{
    QDomElement equivalentRoot = document.createElement("series");
    for (int i = 0; i < this->operators()->size(); ++i)
    {
        QDomElement element = document.createElement("operator");
        element.setAttribute("id", this->operators()->at(i)->realID());
        equivalentRoot.appendChild(element);
    }
    root.appendChild(equivalentRoot);
}

bool GoMarkovEquivalentSeries::tryOpen(QDomElement &root)
{
    if (root.tagName() != "series")
    {
        return false;
    }
    this->_idList->clear();
    for (QDomElement element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        this->_idList->push_back(element.attribute("id").toInt());
    }
    return true;
}
