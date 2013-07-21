#include <qmath.h>
#include "gomarkovoperator9.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator9::GOMarkovOperator9() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->setDualBreakdown(false);
    this->setBreakdownCorrelate(false);
    this->_markovStatus2 = new GOMarkovStatus();
}

GOMarkovOperator9::~GOMarkovOperator9()
{
    this->GOMarkovOperator::~GOMarkovOperator();
    delete this->_markovStatus2;
}

bool GOMarkovOperator9::isDualBreakdown() const
{
    return this->_isDualBreakdown;
}

bool GOMarkovOperator9::isBreakdownCorrelate() const
{
    return this->_isBreakdownCorrelate;
}

void GOMarkovOperator9::setDualBreakdown(bool value)
{
    this->_isDualBreakdown = value;
}

void GOMarkovOperator9::setBreakdownCorrelate(bool value)
{
    this->_isBreakdownCorrelate = value;
}

GOMarkovStatus* GOMarkovOperator9::markovStatus2() const
{
    return this->_markovStatus2;
}

void GOMarkovOperator9::initMarkovStatus(double time, double c12)
{
    if (this->isDualBreakdown())
    {
        double lamda1 = this->markovStatus()->frequencyBreakdown();
        double miu1 = this->markovStatus()->frequencyRepair();
        double lamda2 = this->markovStatus2()->frequencyBreakdown();
        double miu2 = this->markovStatus2()->frequencyRepair();
        double s1 = 0.5 * (-(lamda1 + lamda2 + miu1 + miu2) + sqrt((lamda1 - lamda2 + miu1 - miu2) * (lamda1 - lamda2 + miu1 - miu2) + 4 * lamda1 * lamda2));
        double s2 = 0.5 * (-(lamda1 + lamda2 + miu1 + miu2) - sqrt((lamda1 - lamda2 + miu1 - miu2) * (lamda1 - lamda2 + miu1 - miu2) + 4 * lamda1 * lamda2));
        double p1 = miu1 / s1 * miu2 / s2 +
                (s1 * s1 + (miu1 + miu2) * s1 + miu1 * miu2) / (s1 * (s1 - s2)) * exp(s1 * time) +
                (s2 * s2 + (miu1 + miu2) * s2 + miu1 * miu2) / (s2 * (s2 - s1)) * exp(s2 * time);
        if (p1 > 1.0)
        {
            p1 = 1.0;
        }
        double p2 = 1 - p1;
        this->status()->setProbability(1, p1);
        this->status()->setProbability(2, p2);
    }
    else
    {
        this->GOMarkovOperator::initMarkovStatus(time, c12);
    }
}

void GOMarkovOperator9::calcOutputMarkovStatus(double time)
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

void GOMarkovOperator9::calcOutputMarkovStatusNormal()
{
    GOSignal *signal = this->input()->signal()->at(0);
    GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(this);
    int index = prev->output()->getSignalIndex(signal);
    GOMarkovStatus *prevStatus = prev->markovOutputStatus()->at(index);
    double PS = prevStatus->probabilityNormal();
    double PC = this->markovStatus()->probabilityNormal();
    double PR = PS * PC;
    double QR = 1 - PR;
    double lamdaS = prevStatus->frequencyBreakdown();
    double lamdaC = this->markovStatus()->frequencyBreakdown();
    double lamdaR = lamdaS + lamdaC;
    double miuR = lamdaR * PR / QR;
    this->markovOutputStatus()->clear();
    GOMarkovStatus *outputStatus = new GOMarkovStatus();
    outputStatus->setProbabilityNormal(PR);
    outputStatus->setFrequencyBreakdown(lamdaR);
    outputStatus->setFrequencyRepair(miuR);
    this->markovOutputStatus()->push_back(outputStatus);
}

void GOMarkovOperator9::calcOutputMarkovStatusCorrelate()
{
    GOSignal *signal = this->input()->signal()->at(0);
    GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(this);
    int index = prev->output()->getSignalIndex(signal);
    GOMarkovStatus *prevStatus = prev->markovOutputStatus()->at(index);
    double PS = prevStatus->probabilityNormal();
    double QS = prevStatus->probabilityBreakdown();
    double PC = this->markovStatus()->probabilityNormal();
    double QC = this->markovStatus()->probabilityBreakdown();
    double G1 = PS * PC;
    double G2 = PS * QC + QS * PC;
    double PR = G1 / (G1 + G2);
    double lamdaS = prevStatus->frequencyBreakdown();
    double miuS = prevStatus->frequencyRepair();
    double lamdaC = this->markovStatus()->frequencyBreakdown();
    double miuC = this->markovStatus()->frequencyRepair();
    double lamdaR = lamdaS + lamdaC;
    double miuR = lamdaR / (lamdaS / miuS + lamdaC / miuC);
    this->markovOutputStatus()->clear();
    GOMarkovStatus *outputStatus = new GOMarkovStatus();
    outputStatus->setProbabilityNormal(PR);
    outputStatus->setFrequencyBreakdown(lamdaR);
    outputStatus->setFrequencyRepair(miuR);
    this->markovOutputStatus()->push_back(outputStatus);
}

void GOMarkovOperator9::save(QDomDocument &document, QDomElement &root)
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
    this->markovStatus2()->save(document, element);
    this->parameter()->save(document, element);
}

bool GOMarkovOperator9::tryOpen(QDomElement &root)
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
    if (!this->markovStatus2()->tryOpen(element))
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
