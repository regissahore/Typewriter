#include <cstdio>
#include <qmath.h>
#include "gomarkovoperator.h"
#include "gomarkovstatus.h"
#include "goinput.h"
#include "gooutput.h"
#include "goparameter.h"
#include "gostatus.h"

GOMarkovOperator::GOMarkovOperator() : GOOperator()
{
    this->_markovStatus = new GOMarkovStatus();
    this->_outputStatus = new QVector<GOMarkovStatus*>();
}

GOMarkovOperator::~GOMarkovOperator()
{
    this->GOOperator::~GOOperator();
    delete this->_markovStatus;
    for (int i = 0; i < this->_outputStatus->size(); ++i)
    {
        delete this->_outputStatus->at(i);
    }
    delete this->_outputStatus;
}

GOMarkovStatus* GOMarkovOperator::markovStatus() const
{
    return this->_markovStatus;
}

QVector<GOMarkovStatus*>* GOMarkovOperator::markovOutputStatus() const
{
    return this->_outputStatus;
}

void GOMarkovOperator::initMarkovStatus(double time, double c12)
{
    double lamda = this->markovStatus()->frequencyBreakdown();
    double miu = this->markovStatus()->frequencyRepair();
    double p1 = miu / (lamda + miu) * (1 + lamda / miu * exp(-(lamda + miu) * time)) + c12;
    if (p1 > 1.0)
    {
        p1 = 1.0;
    }
    double p2 = 1 - p1;
    this->status()->setProbability(1, p1);
    this->status()->setProbability(2, p2);
}

void GOMarkovOperator::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
}

double GOMarkovOperator::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput)
{
    Q_UNUSED(time);
    Q_UNUSED(input);
    Q_UNUSED(subInput);
    return 0.0;
}

void GOMarkovOperator::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->parameter()->save(document, element);
}

bool GOMarkovOperator::tryOpen(QDomElement &root)
{
    if (root.tagName() != "model")
    {
        return false;
    }
    this->setType(root.attribute("type").toInt());
    this->setId(root.attribute("id").toInt());
    this->input()->setNumber(root.attribute("input").toInt());
    this->subInput()->setNumber(root.attribute("subInput").toInt());
    this->output()->setNumber(root.attribute("output").toInt());
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
    if (!this->parameter()->tryOpen(element))
    {
        return false;
    }
    return true;
}
