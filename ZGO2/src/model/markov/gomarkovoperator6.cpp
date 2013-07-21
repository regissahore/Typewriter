#include <qmath.h>
#include "gomarkovoperator6.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator6::GOMarkovOperator6() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(1);
    this->output()->setNumber(1);
    this->setBreakdownCorrelate(false);
}

GOMarkovOperator6::~GOMarkovOperator6()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

bool GOMarkovOperator6::isBreakdownCorrelate() const
{
    return this->_isBreakdownCorrelate;
}

void GOMarkovOperator6::setBreakdownCorrelate(bool value)
{
    this->_isBreakdownCorrelate = value;
}

void GOMarkovOperator6::calcOutputMarkovStatus(double time)
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

double GOMarkovOperator6::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput)
{
    Q_UNUSED(time);
    if (this->isBreakdownCorrelate())
    {
        return this->calcTempOutputMarkovStatusCorrelate(input[0], subInput[0]);
    }
    return this->calcTempOutputMarkovStatusNormal(input[0], subInput[0]);
}

void GOMarkovOperator6::calcCommonOutputMarkovStatus(double PR)
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

void GOMarkovOperator6::calcOutputMarkovStatusNormal()
{
    GOMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GOMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
    double PS1 = prevStatus1->probabilityNormal();
    double PS2 = prevStatus2->probabilityNormal();
    double PC = this->markovStatus()->probabilityNormal();
    double PR = PS1 * PS2 * PC;
    double QR = 1 - PR;
    double lambdaS1 = prevStatus1->frequencyBreakdown();
    double lambdaS2 = prevStatus2->frequencyBreakdown();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double lambdaR = lambdaS1 + lambdaS2 + lambdaC;
    double muR = lambdaR * PR / QR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator6::calcCommonOutputMarkovStatusNormal(double PR)
{
    double QR = 1.0 - PR;
    GOMarkovStatus* prevStatus1 = this->getPrevMarkovStatus();
    GOMarkovStatus* prevStatus2 = this->getPrevSubMarkovStatus();
    double lambdaS1 = prevStatus1->frequencyBreakdown();
    double lambdaS2 = prevStatus2->frequencyBreakdown();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double lambdaR = lambdaS1 + lambdaS2 + lambdaC;
    double muR = lambdaR * PR / QR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator6::calcTempOutputMarkovStatusNormal(double PS1, double PS2)
{
    double PC = this->markovStatus()->probabilityNormal();
    return PS1 * PS2 * PC;
}

void GOMarkovOperator6::calcOutputMarkovStatusCorrelate()
{
}

void GOMarkovOperator6::calcCommonOutputMarkovStatusCorrelate(double PR)
{

}

double GOMarkovOperator6::calcTempOutputMarkovStatusCorrelate(double PS1, double PS2)
{

}

void GOMarkovOperator6::save(QDomDocument &document, QDomElement &root)
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

bool GOMarkovOperator6::tryOpen(QDomElement &root)
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
