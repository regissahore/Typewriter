#include <QObject>
#include <qmath.h>
#include "gomarkovcommoncause.h"
#include "gomarkovoperator.h"
#include "gomarkovstatus.h"
#include "qmath.h"
#include "messagecontroller.h"
#include "messagefactory.h"
#include "messager.h"
#include "gomarkovoperatorfactory.h"

GOMarkovCommonCause::GOMarkovCommonCause() : DomItem()
{
    this->_breakdownTotal = 0.0;
    this->_breakdownIndividual = 0.0;
    this->_breakdownCommon = 0.0;
    this->_belta = 0.0;
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

double GOMarkovCommonCause::breakdownCommon() const
{
    return this->_breakdownCommon;
}

void GOMarkovCommonCause::setBreakdownCommon(double value)
{
    this->_breakdownCommon = value;
}

double GOMarkovCommonCause::belta() const
{
    return this->_belta;
}

void GOMarkovCommonCause::setBelta(double value)
{
    this->_belta = value;
    this->_breakdownCommon = this->_breakdownTotal * value;
    this->_breakdownIndividual =this->_breakdownTotal * (1.0 - value);
}

double GOMarkovCommonCause::gammaC() const
{
    return this->_gammaC;
}

void GOMarkovCommonCause::setGammaC(double value)
{
    this->_gammaC = value;
}

GOMarkovCommonCause* GOMarkovCommonCause::copy() const
{
    GOMarkovCommonCause *common = new GOMarkovCommonCause();
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

void GOMarkovCommonCause::save(QDomDocument &document, QDomElement &root)
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

bool GOMarkovCommonCause::tryOpen(QDomElement &root)
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
    double muSum = 0.0;
    for (int j = 0; j < this->operators()->size(); ++j)
    {
        GOMarkovOperator *op = (GOMarkovOperator*)this->operators()->at(j);
        muSum += op->markovStatus1()->frequencyRepair();
    }
    double c = this->breakdownCommon();
    double p1 = c / (c + muSum);
    double p2 = exp(-(c + muSum) * time);
    double c12 = p1 + (this->gammaC() - p1) * p2;
    return c12;
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

bool GOMarkovCommonCause::errorDetect(Messager *messager)
{
    if (this->_operators->size() > 0)
    {
        double lambda1 = this->_operators->at(0)->markovStatus1()->frequencyBreakdown();
        for (int i = 1; i < this->_operators->size(); ++i)
        {
            double lambda2 = this->_operators->at(i)->markovStatus1()->frequencyBreakdown();
            if (fabs(lambda1 - lambda2) > 1e-8)
            {
                Message *message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_ERROR);
                message->paramString = QObject::tr("Error: Common Cause ") + QObject::tr("%1 %2 should have same breakdown frequency. ").arg(this->_operators->at(0)->id()).arg(this->_operators->at(i)->id());
                messager->sendMessage(message);
                return true;
            }
        }
    }
    return false;
}
