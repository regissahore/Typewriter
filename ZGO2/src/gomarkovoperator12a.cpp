#include <QObject>
#include <QPainter>
#include <qmath.h>
#include "gomarkovoperator12a.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"
#include "messager.h"
#include "messagefactory.h"
#include "gomarkovoperatorfactory.h"

GOMarkovOperator12A::GOMarkovOperator12A() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(3);
    this->setIsUseDelta(false);
    this->_deltaNum = 1;
    this->_ids = new QVector<QString>();
    this->_delta = new QVector<double>();
    this->_ids->push_back("0");
    this->_delta->push_back(0.0);
}

GOMarkovOperator12A::~GOMarkovOperator12A()
{
    this->GOMarkovOperator::~GOMarkovOperator();
    this->_ids->clear();
    delete this->_ids;
    this->_delta->clear();
    delete this->_delta;
}

void GOMarkovOperator12A::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GOMarkovStatus *prevStatus = this->getPrevMarkovStatus();
    DoubleVector PR = prevStatus->probabilityNormal();
    DoubleVector lambdaR = prevStatus->frequencyBreakdown();
    DoubleVector muR = prevStatus->frequencyRepair();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR.getValue(i));
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR.getValue(i));
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR.getValue(i));
    }
}

DoubleVector GOMarkovOperator12A::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    return input[0].getValue(index);
}

QVector<QString>* GOMarkovOperator12A::ids() const
{
    return this->_ids;
}

QVector<double>* GOMarkovOperator12A::delta() const
{
    return this->_delta;
}

bool GOMarkovOperator12A::isUseDelta() const
{
    return this->_isUseDelta;
}

void GOMarkovOperator12A::setIsUseDelta(const bool value)
{
    this->_isUseDelta = value;
    if (value)
    {
        this->setDeltaNum(this->output()->number() - 1);
    }
}

int GOMarkovOperator12A::deltaNum() const
{
    return this->_deltaNum;
}

void GOMarkovOperator12A::setDeltaNum(int value)
{
    this->_deltaNum = value;
    for (int i = this->_delta->size(); i < value; ++i)
    {
        this->_ids->push_back("0");
        this->_delta->push_back(0.0);
    }
}

void GOMarkovOperator12A::calcOutputMarkovStatus(QVector<GOMarkovStatus> prevStatus)
{
    for (int i = 0; i < this->output()->number(); ++i)
    {
        this->markovOutputStatus()->at(i)->setProbabilityNormal(prevStatus[i].probabilityNormal());
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(prevStatus[i].frequencyBreakdown());
        this->markovOutputStatus()->at(i)->setFrequencyRepair(prevStatus[i].frequencyRepair());
    }
}

void GOMarkovOperator12A::paintParameter(QPainter *painter)
{
    int y = 40;
    if (this->isUseDelta())
    {
        painter->drawText(-50, y, QObject::tr("Relvent"));
        for (int i = 0; i < this->deltaNum(); ++i)
        {
            y += 20;
            painter->drawText(-50, y, QString("%1: %2").arg(this->ids()->at(i)).arg(this->delta()->at(i)));
        }
    }
}

GOMarkovOperator* GOMarkovOperator12A::copy()
{
    GOMarkovOperator12A *op = (GOMarkovOperator12A*)this->GOMarkovOperator::copy();
    op->setIsUseDelta(this->isUseDelta());
    op->setDeltaNum(this->deltaNum());
    return op;
}

void GOMarkovOperator12A::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("real", this->realID());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    element.setAttribute("dual", this->breakdownNum());
    element.setAttribute("breakdown", this->isBreakdownCorrelate());
    element.setAttribute("global_feedback", this->isGlobalFeedback());
    element.setAttribute("name", this->name());
    element.setAttribute("use_delta", this->isUseDelta());
    element.setAttribute("delta", this->deltaNum());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->markovStatus3()->save(document, element);
    this->markovStatus4()->save(document, element);
    QDomElement subElement = document.createElement("markov2");
    for (int i = 0; i < this->deltaNum(); ++i)
    {
        QDomElement node = document.createElement("node");
        node.setAttribute("a", this->ids()->at(i));
        node.setAttribute("delta", this->delta()->at(i));
        subElement.appendChild(node);
    }
    element.appendChild(subElement);
}

bool GOMarkovOperator12A::tryOpen(QDomElement &root)
{
    if (root.tagName() != "model")
    {
        return false;
    }
    this->setType(root.attribute("type").toInt());
    this->setId(root.attribute("id").toInt());
    if (root.hasAttribute("real"))
    {
        this->setRealID(root.attribute("real").toInt());
    }
    else
    {
        this->setRealID(root.attribute("id").toInt());
    }
    this->input()->setNumber(root.attribute("input").toInt());
    this->subInput()->setNumber(root.attribute("subInput").toInt());
    this->output()->setNumber(root.attribute("output").toInt());
    this->setBreakdownNum(root.attribute("dual").toInt());
    this->setBreakdownCorrelate(root.attribute("breakdown").toInt());
    this->setIsGlobalFeedback(root.attribute("global_feedback", "0").toInt());
    this->setName(root.attribute("name", ""));
    this->setIsUseDelta(root.attribute("use_delta").toInt());
    this->setDeltaNum(root.attribute("delta").toInt());
    QDomElement element = root.firstChildElement();
    if (!this->status()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->markovStatus()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->markovStatus1()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->markovStatus2()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->markovStatus3()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->markovStatus4()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    QDomElement node = element.firstChildElement();
    this->ids()->clear();
    this->delta()->clear();
    for (int i = 0; i < this->deltaNum(); ++i)
    {
        this->ids()->push_back(node.attribute("a"));
        this->delta()->push_back(node.attribute("delta").toDouble());
        node = node.nextSiblingElement();
    }
    return true;
}
