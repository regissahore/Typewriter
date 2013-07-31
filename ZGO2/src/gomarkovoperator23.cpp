#include <qmath.h>
#include "gomarkovoperator23.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator23::GOMarkovOperator23() : GOMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->_alpha = new QVector<double>();
}

GOMarkovOperator23::~GOMarkovOperator23()
{
    this->GOMarkovOperator::~GOMarkovOperator();
    this->_alpha->clear();
    delete this->_alpha;
}

QVector<double>* GOMarkovOperator23::alpha() const
{
    return this->_alpha;
}

void GOMarkovOperator23::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    double PR = 0.0;
    double lambdaR = 0.0;
    double muR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *status = this->getPrevMarkovStatus(i);
        double PS = status->probabilityNormal();
        double lambdaS = status->frequencyBreakdown();
        double muS = status->frequencyRepair();
        PR += PS * this->alpha()->at(i);
        lambdaR += lambdaS * this->alpha()->at(i);
        muR += muS * this->alpha()->at(i);
    }
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator23::calcCommonOutputMarkovStatus(QVector<double> PR)
{
    double lambdaR = 0.0;
    double muR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *status = this->getPrevMarkovStatus(i);
        double lambdaS = status->frequencyBreakdown();
        double muS = status->frequencyRepair();
        lambdaR += lambdaS * this->alpha()->at(i);
        muR += muS * this->alpha()->at(i);
    }
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator23::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    double PR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        double PS = input[i];
        PR += PS * this->alpha()->at(i);
    }
    return PR;
}

GOMarkovOperator* GOMarkovOperator23::copy()
{
    GOMarkovOperator23 *op = (GOMarkovOperator23*)this->GOMarkovOperator::copy();
    for (int i = 0; i < this->input()->number(); ++i)
    {
        op->alpha()->push_back(this->alpha()->at(i));
    }
    return op;
}

void GOMarkovOperator23::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    element.setAttribute("dual", this->isDualBreakdown());
    element.setAttribute("breakdown", this->isBreakdownCorrelate());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    QDomElement subElement = document.createElement("markov2");
    for (int i = 0; i < this->input()->number(); ++i)
    {
        QDomElement node = document.createElement("node");
        node.setAttribute("alpha", this->alpha()->at(i));
        subElement.appendChild(node);
    }
    element.appendChild(subElement);
}

bool GOMarkovOperator23::tryOpen(QDomElement &root)
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
    this->setDualBreakdown(root.attribute("dual").toInt());
    this->setBreakdownCorrelate(root.attribute("breakdown").toInt());
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
    QDomElement node = element.firstChildElement();
    for (int i = 0; i < this->input()->number(); ++i)
    {
        this->alpha()->push_back(node.attribute("alpha").toDouble());
        node = node.nextSiblingElement();
    }
    return true;
}
