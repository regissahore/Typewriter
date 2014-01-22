#include <QObject>
#include <qmath.h>
#include "GoMarkovCommonCause.h"
#include "GoMarkovOperator.h"
#include "GoMarkovStatus.h"
#include "qmath.h"
#include "MessageController.h"
#include "MessageFactory.h"
#include "Messager.h"
#include "GoMarkovOperatorFactory.h"

GoMarkovCommonCause::GoMarkovCommonCause() : DomItem()
{
    this->_breakdownTotal = 0.0;
    this->_breakdownIndividual = 0.0;
    this->_breakdownCommon = 0.0;
    this->_belta = 0.0;
    this->_gammaC = 1.0;
    this->_idList = new QVector<int>();
    this->_operators = new QVector<GoMarkovOperator*>();
    this->_error = "";
}

GoMarkovCommonCause::~GoMarkovCommonCause()
{
    this->_idList->clear();
    delete this->_idList;
    this->_operators->clear();
    delete this->_operators;
}

double GoMarkovCommonCause::breakdownTotal() const
{
    return this->_breakdownTotal;
}

void GoMarkovCommonCause::setBreakdownTotal(double value)
{
    this->_breakdownTotal = value;
}

double GoMarkovCommonCause::breakdownIndividual() const
{
    return this->_breakdownIndividual;
}

void GoMarkovCommonCause::setBreakdownIndividual(double value)
{
    this->_breakdownIndividual = value;
}

double GoMarkovCommonCause::breakdownCommon() const
{
    return this->_breakdownCommon;
}

void GoMarkovCommonCause::setBreakdownCommon(double value)
{
    this->_breakdownCommon = value;
}

double GoMarkovCommonCause::belta() const
{
    return this->_belta;
}

void GoMarkovCommonCause::setBelta(double value)
{
    this->_belta = value;
    this->_breakdownCommon = this->_breakdownTotal * value;
    this->_breakdownIndividual =this->_breakdownTotal * (1.0 - value);
}

double GoMarkovCommonCause::gammaC() const
{
    return this->_gammaC;
}

void GoMarkovCommonCause::setGammaC(double value)
{
    this->_gammaC = value;
}

QString GoMarkovCommonCause::error() const
{
    return this->_error;
}

GoMarkovCommonCause* GoMarkovCommonCause::copy() const
{
    GoMarkovCommonCause *common = new GoMarkovCommonCause();
    for (int i = 0; i < this->_idList->size(); ++i)
    {
        common->_idList->push_back(this->_idList->at(i));
    }
    for (int i = 0; i < this->_operators->size(); ++i)
    {
        common->_operators->push_back(0L);
    }
    common->_breakdownTotal = this->_breakdownTotal;
    common->_breakdownIndividual = this->_breakdownIndividual;
    common->_breakdownCommon = this->_breakdownCommon;
    common->_belta = this->_belta;
    common->_gammaC = this->_gammaC;
    return common;
}

void GoMarkovCommonCause::save(QDomDocument &document, QDomElement &root)
{
    QDomElement commonRoot = document.createElement("commoncause");
    commonRoot.setAttribute("total", this->breakdownTotal());
    commonRoot.setAttribute("individual", this->breakdownIndividual());
    commonRoot.setAttribute("common", this->breakdownCommon());
    commonRoot.setAttribute("belta", this->belta());
    commonRoot.setAttribute("gammac", this->gammaC());
    for (int i = 0; i < this->operators()->size(); ++i)
    {
        QDomElement element = document.createElement("operator");
        element.setAttribute("id", this->operators()->at(i)->realID());
        commonRoot.appendChild(element);
    }
    root.appendChild(commonRoot);
}

bool GoMarkovCommonCause::tryOpen(QDomElement &root)
{
    if (root.tagName() != "commoncause")
    {
        return false;
    }
    this->setBreakdownTotal(root.attribute("total").toDouble());
    this->setBreakdownIndividual(root.attribute("individual").toDouble());
    this->setBreakdownCommon(root.attribute("common").toDouble());
    this->_belta = root.attribute("belta").toDouble();
    this->setGammaC(root.attribute("gammac").toDouble());
    this->_idList->clear();
    for (QDomElement element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        this->_idList->push_back(element.attribute("id").toInt());
    }
    return true;
}

QVector<GoMarkovOperator*>* GoMarkovCommonCause::operators() const
{
    return this->_operators;
}

QVector<int>* GoMarkovCommonCause::idList() const
{
    return this->_idList;
}

double GoMarkovCommonCause::calcCommonCause(double time) const
{
    double muSum = 0.0;
    for (int j = 0; j < this->operators()->size(); ++j)
    {
        GoMarkovOperator *op = (GoMarkovOperator*)this->operators()->at(j);
        muSum += op->markovStatus()->frequencyRepair().getValue(0);
    }
    double c = this->breakdownCommon();
    double p1 = c / (c + muSum);
    double p2 = exp(-(c + muSum) * time);
    double c12 = p1 + (this->gammaC() - p1) * p2;
    return c12;
}

bool GoMarkovCommonCause::containOperator(GoMarkovOperator* op) const
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

bool GoMarkovCommonCause::errorDetect()
{
    if (this->_operators->size() > 0)
    {
        double lambda1 = this->_operators->at(0)->totalFrequencyBreakdown().getValue(0);
        for (int i = 1; i < this->_operators->size(); ++i)
        {
            double lambda2 = this->_operators->at(i)->totalFrequencyBreakdown().getValue(0);
            if (fabs(lambda1 - lambda2) > 1e-8)
            {
                this->_error = QObject::tr("Error: Common Cause ") + QObject::tr("%1 %2 should have same breakdown frequency. ").arg(this->_operators->at(0)->id()).arg(this->_operators->at(i)->id());
                return true;
            }
        }
    }
    return false;
}
