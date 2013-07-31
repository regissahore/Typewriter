#include "gomarkovcommoncause.h"
#include "gomarkovoperator.h"
#include "gomarkovstatus.h"
#include "qmath.h"

GOMarkovCommonCause::GOMarkovCommonCause() : DomItem()
{
    this->_breakdownTotal = 0.0;
    this->_breakdownIndividual = 0.0;
    this->_gammaC = 1.0;
    this->_idList = new QVector<int>();
    this->_operators = new QVector<GOMarkovOperator*>();
}

GOMarkovCommonCause::~GOMarkovCommonCause()
{
    this->_idList->clear();
    delete this->_idList;
    this->_operators->clear();
    delete this->_operators;
}

double GOMarkovCommonCause::breakdownTotal() const
{
    return this->_breakdownTotal;
}

void GOMarkovCommonCause::setBreakdownTotal(double value)
{
    this->_breakdownTotal = value;
}

double GOMarkovCommonCause::breakdownIndividual() const
{
    return this->_breakdownIndividual;
}

void GOMarkovCommonCause::setBreakdownIndividual(double value)
{
    this->_breakdownIndividual = value;
}

double GOMarkovCommonCause::gammaC() const
{
    return this->_gammaC;
}

void GOMarkovCommonCause::setGammaC(double value)
{
    this->_gammaC = value;
}

double GOMarkovCommonCause::breakdownCommon() const
{
    return this->breakdownTotal() - this->breakdownIndividual();
}

void GOMarkovCommonCause::save(QDomDocument &document, QDomElement &root)
{
    QDomElement commonRoot = document.createElement("commoncause");
    commonRoot.setAttribute("total", this->breakdownTotal());
    commonRoot.setAttribute("individual", this->breakdownIndividual());
    commonRoot.setAttribute("gammac", this->gammaC());
    for (int i = 0; i < this->operators()->size(); ++i)
    {
        QDomElement element = document.createElement("operator");
        element.setAttribute("id", this->operators()->at(i)->id());
        commonRoot.appendChild(element);
    }
    root.appendChild(commonRoot);
}

bool GOMarkovCommonCause::tryOpen(QDomElement &root)
{
    if (root.tagName() != "commoncause")
    {
        return false;
    }
    this->setBreakdownTotal(root.attribute("total").toDouble());
    this->setBreakdownIndividual(root.attribute("individual").toDouble());
    this->setGammaC(root.attribute("gammac").toDouble());
    this->_idList->clear();
    for (QDomElement element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        this->_idList->push_back(element.attribute("id").toInt());
    }
    return true;
}

QVector<GOMarkovOperator*>* GOMarkovCommonCause::operators() const
{
    return this->_operators;
}

QVector<int>* GOMarkovCommonCause::idList() const
{
    return this->_idList;
}

double GOMarkovCommonCause::calcCommonCause(double time) const
{
    double miuSum = 0.0;
    for (int j = 0; j < this->operators()->size(); ++j)
    {
        GOMarkovOperator *op = (GOMarkovOperator*)this->operators()->at(j);
        miuSum += op->markovStatus()->frequencyRepair();
    }
    double c = this->breakdownCommon();
    double c12 = c / (c + miuSum) + (this->gammaC() - c / (c + miuSum)) * exp(-(c + miuSum) * time);
    return 1.0 - c12;
}

bool GOMarkovCommonCause::containOperator(GOMarkovOperator* op) const
{
    for (int i = 0; i < this->_operators->size(); ++i)
    {
        if (this->_operators->at(i) == op)
        {
            return true;
        }
    }
    return false;
}
