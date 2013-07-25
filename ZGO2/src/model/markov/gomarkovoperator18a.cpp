#include <qmath.h>
#include "gomarkovoperator18a.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator18A::GOMarkovOperator18A() : GOMarkovOperator()
{
    this->input()->setNumber(2);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->setBackup(0.0);
}

GOMarkovOperator18A::~GOMarkovOperator18A()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

double GOMarkovOperator18A::backup() const
{
    return this->_backup;
}

void GOMarkovOperator18A::setBackup(double value)
{
    this->_backup = value;
}

void GOMarkovOperator18A::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GOMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    GOMarkovStatus *status2 = this->getPrevMarkovStatus(1);
    double PS1 = status1->probabilityNormal();
    double PS2 = status2->probabilityNormal();
    double lambdaS1 = status1->frequencyBreakdown();
    double muS1 = status1->frequencyRepair();
    double muS2 = status2->frequencyRepair();
    double P0 = PS1 * this->backup();
    double PR = PS1 + PS2;
    if (PR > 1.0)
    {
        PR = 1.0;
    }
    double muR = muS1 + muS2;
    double lambdaR = (lambdaS1 * (PS1 - P0) + lambdaS1 * PS2) / PR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator18A::calcCommonOutputMarkovStatus(QVector<double> PR)
{
    GOMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    GOMarkovStatus *status2 = this->getPrevMarkovStatus(1);
    double PS1 = status1->probabilityNormal();
    double PS2 = status2->probabilityNormal();
    double lambdaS1 = status1->frequencyBreakdown();
    double muS1 = status1->frequencyRepair();
    double muS2 = status2->frequencyRepair();
    double P0 = PS1 * this->backup();
    double muR = muS1 + muS2;
    double lambdaR = (lambdaS1 * (PS1 - P0) + lambdaS1 * PS2) / PR[0];
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator18A::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    double PS1 = input[0];
    double PS2 = input[1];
    double PR = PS1 + PS2;
    if (PR > 1.0)
    {
        PR = 1.0;
    }
    return PR;
}

GOMarkovOperator* GOMarkovOperator18A::copy()
{
    GOMarkovOperator18A *op = new GOMarkovOperator18A();
    op->setType(this->TypedItem::type());
    op->input()->setNumber(this->input()->number());
    op->subInput()->setNumber(this->subInput()->number());
    op->output()->setNumber(this->output()->number());

    op->setDualBreakdown(this->isDualBreakdown());
    op->setBreakdownCorrelate(this->isBreakdownCorrelate());

    op->markovStatus()->setProbabilityNormal(this->markovStatus()->probabilityNormal());
    op->markovStatus()->setFrequencyBreakdown(this->markovStatus()->frequencyBreakdown());
    op->markovStatus()->setFrequencyRepair(this->markovStatus()->frequencyRepair());

    op->markovStatus1()->setProbabilityNormal(this->markovStatus1()->probabilityNormal());
    op->markovStatus1()->setFrequencyBreakdown(this->markovStatus1()->frequencyBreakdown());
    op->markovStatus1()->setFrequencyRepair(this->markovStatus1()->frequencyRepair());

    op->markovStatus2()->setProbabilityNormal(this->markovStatus2()->probabilityNormal());
    op->markovStatus2()->setFrequencyBreakdown(this->markovStatus2()->frequencyBreakdown());
    op->markovStatus2()->setFrequencyRepair(this->markovStatus2()->frequencyRepair());

    op->setBackup(this->backup());
    return op;
}

void GOMarkovOperator18A::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    element.setAttribute("backup", this->backup());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
}

bool GOMarkovOperator18A::tryOpen(QDomElement &root)
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
    this->setBackup(root.attribute("backup").toDouble());
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
    return true;
}
