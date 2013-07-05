#include "gomarkovequivalentseries.h"
#include "gomarkovstatus.h"
#include "gomarkovoperator.h"

GOMarkovEquivalentSeries::GOMarkovEquivalentSeries() : GOMarkovEquivalent()
{
}

GOMarkovStatus GOMarkovEquivalentSeries::getEquivalentStatus()
{
    GOMarkovStatus status;
    if (this->I() == 1)
    {
        double lamda = 0.0;
        double lamdaFracSum = 0.0;
        for (int i = 0; i < this->_operators->size(); ++i)
        {
            lamda = lamda + this->_operators->at(i)->markovStatus()->frequencyBreakdown();
            lamdaFracSum = lamdaFracSum + this->_operators->at(i)->markovStatus()->frequencyBreakdown() / this->_operators->at(i)->markovStatus()->frequencyRepair();
        }
        double miu = lamda / lamdaFracSum;
        status.setFrequencyBreakdown(lamda);
        status.setFrequencyRepair(miu);
    }
    else
    {
        double lamda = 0.0;
        double p1 = 1.0;
        for (int i = 0; i < this->_operators->size(); ++i)
        {
            lamda = lamda + this->_operators->at(i)->markovStatus()->frequencyBreakdown();
            p1 = p1 * this->_operators->at(i)->markovStatus()->probabilityNormal();
        }
        double miu = lamda * p1 / (1.0 - p1);
        status.setFrequencyBreakdown(lamda);
        status.setFrequencyRepair(miu);
    }
    return status;
}

void GOMarkovEquivalentSeries::save(QDomDocument &document, QDomElement &root)
{
    QDomElement equivalentRoot = document.createElement("series");
    for (int i = 0; i < this->operators()->size(); ++i)
    {
        QDomElement element = document.createElement("operator");
        element.setAttribute("id", this->operators()->at(i)->id());
        equivalentRoot.appendChild(element);
    }
    root.appendChild(equivalentRoot);
}

bool GOMarkovEquivalentSeries::tryOpen(QDomElement &root)
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
