#include <qmath.h>
#include "gomarkovoperator10.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator10::GOMarkovOperator10() : GOMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->setBreakdownCorrelate(false);
}

GOMarkovOperator10::~GOMarkovOperator10()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

bool GOMarkovOperator10::isBreakdownCorrelate() const
{
    return this->_isBreakdownCorrelate;
}

void GOMarkovOperator10::setBreakdownCorrelate(bool value)
{
    this->_isBreakdownCorrelate = value;
}

void GOMarkovOperator10::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    if (this->isBreakdownCorrelate())
    {
        this->calcOutputMarkovStatusCorrelate();
    }
    else
    {
        this->calcOutputMarkovStatusNormal();
    }
}

void GOMarkovOperator10::calcCommonOutputMarkovStatus(double PR)
{
    Q_UNUSED(time);
    if (this->isBreakdownCorrelate())
    {
        this->calcCommonOutputMarkovStatusCorrelate(PR);
    }
    else
    {
        this->calcCommonOutputMarkovStatusNormal(PR);
    }
}

double GOMarkovOperator10::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    if (this->isBreakdownCorrelate())
    {
        return this->calcTempOutputMarkovStatusCorrelate(input);
    }
    return this->calcTempOutputMarkovStatusNormal(input);
}

void GOMarkovOperator10::calcOutputMarkovStatusNormal()
{
    double PR = 1.0;
    double lambdaR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        double PSi = prevStatus->probabilityNormal();
        double lambdaSi = prevStatus->frequencyBreakdown();
        PR *= PSi;
        lambdaR += lambdaSi;
    }
    double QR = 1.0 - PR;
    double muR = lambdaR * PR / QR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator10::calcCommonOutputMarkovStatusNormal(double PR)
{
    double lambdaR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        double lambdaSi = prevStatus->frequencyBreakdown();
        lambdaR += lambdaSi;
    }
    double QR = 1.0 - PR;
    double muR = lambdaR * PR / QR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator10::calcTempOutputMarkovStatusNormal(QVector<double> input)
{
    double PR = 1.0;
    for (int i = 0; i < input.size(); ++i)
    {
        PR *= input[i];
    }
    return PR;
}

void GOMarkovOperator10::calcOutputMarkovStatusCorrelate()
{
}

void GOMarkovOperator10::calcCommonOutputMarkovStatusCorrelate(double PR)
{

}

double GOMarkovOperator10::calcTempOutputMarkovStatusCorrelate(QVector<double> input)
{

}

void GOMarkovOperator10::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    element.setAttribute("breakdown", this->isBreakdownCorrelate());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->parameter()->save(document, element);
}

bool GOMarkovOperator10::tryOpen(QDomElement &root)
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
    if (!this->parameter()->tryOpen(element))
    {
        return false;
    }
    return true;
}
