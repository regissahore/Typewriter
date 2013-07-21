#include <qmath.h>
#include "gomarkovoperator1.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator1::GOMarkovOperator1() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->setDualBreakdown(false);
    this->setBreakdownCorrelate(false);
    this->_markovStatus2 = new GOMarkovStatus();
}

GOMarkovOperator1::~GOMarkovOperator1()
{
    this->GOMarkovOperator::~GOMarkovOperator();
    delete this->_markovStatus2;
}

bool GOMarkovOperator1::isDualBreakdown() const
{
    return this->_isDualBreakdown;
}

bool GOMarkovOperator1::isBreakdownCorrelate() const
{
    return this->_isBreakdownCorrelate;
}

void GOMarkovOperator1::setDualBreakdown(bool value)
{
    this->_isDualBreakdown = value;
}

void GOMarkovOperator1::setBreakdownCorrelate(bool value)
{
    this->_isBreakdownCorrelate = value;
}

GOMarkovStatus* GOMarkovOperator1::markovStatus2() const
{
    return this->_markovStatus2;
}

void GOMarkovOperator1::initMarkovStatus(double time, double c12)
{
    if (this->isDualBreakdown())
    {
        double lamda1 = this->markovStatus()->frequencyBreakdown();
        double miu1 = this->markovStatus()->frequencyRepair();
        double lamda2 = this->markovStatus2()->frequencyBreakdown();
        double miu2 = this->markovStatus2()->frequencyRepair();
        double s1 = 0.5 * (-(lamda1 + lamda2 + miu1 + miu2) + sqrt((lamda1 - lamda2 + miu1 - miu2) * (lamda1 - lamda2 + miu1 - miu2) + 4 * lamda1 * lamda2));
        double s2 = 0.5 * (-(lamda1 + lamda2 + miu1 + miu2) - sqrt((lamda1 - lamda2 + miu1 - miu2) * (lamda1 - lamda2 + miu1 - miu2) + 4 * lamda1 * lamda2));
        double p1 = miu1 * miu2 / s1 / s2 +
                (s1 * s1 + (miu1 + miu2) * s1 + miu1 * miu2) / (s1 * (s1 - s2)) * exp(s1 * time) +
                (s2 * s2 + (miu1 + miu2) * s2 + miu1 * miu2) / (s2 * (s2 - s1)) * exp(s2 * time);
        this->markovStatus()->setProbabilityNormal(p1);
    }
    else
    {
        this->GOMarkovOperator::initMarkovStatus(time, c12);
    }
}

void GOMarkovOperator1::calcOutputMarkovStatus(double time)
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

double GOMarkovOperator1::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    if (this->isBreakdownCorrelate())
    {
        return this->calcTempOutputMarkovStatusCorrelate(input[0]);
    }
    return this->calcTempOutputMarkovStatusNormal(input[0]);
}

void GOMarkovOperator1::calcOutputMarkovStatusNormal()
{
    GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(0);
    double PS = prevStatus->probabilityNormal();
    double PC = this->markovStatus()->probabilityNormal();
    double PR = PS * PC;
    double QR = 1 - PR;
    double lamdaS = prevStatus->frequencyBreakdown();
    double lamdaC = this->markovStatus()->frequencyBreakdown();
    double lamdaR = lamdaS + lamdaC;
    if (this->isDualBreakdown())
    {
        lamdaR += this->markovStatus2()->frequencyBreakdown();
    }
    double miuR = lamdaR * PR / QR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

double GOMarkovOperator1::calcTempOutputMarkovStatusNormal(double PS)
{
    double PC = this->markovStatus()->probabilityNormal();
    return PS * PC;
}

void GOMarkovOperator1::calcOutputMarkovStatusCorrelate()
{
    GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(0);
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
    if (this->isDualBreakdown())
    {
        lamdaR += this->markovStatus2()->frequencyBreakdown();
    }
    double miuR = lamdaR / (lamdaS / miuS + lamdaC / miuC);
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lamdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

double GOMarkovOperator1::calcTempOutputMarkovStatusCorrelate(double PS)
{
    double QS = 1 - PS;
    double PC = this->markovStatus()->probabilityNormal();
    double QC = 1 - PC;
    double G1 = PS * PC;
    double G2 = PS * QC + QS * PC;
    return G1 / (G1 + G2);
}

void GOMarkovOperator1::save(QDomDocument &document, QDomElement &root)
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
    this->markovStatus2()->save(document, element);
    this->parameter()->save(document, element);
}

bool GOMarkovOperator1::tryOpen(QDomElement &root)
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
