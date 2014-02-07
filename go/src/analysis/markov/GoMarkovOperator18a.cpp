#include <qmath.h>
#include "GoMarkovOperator18a.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator18A::GoMarkovOperator18A() : GoMarkovOperator()
{
    this->input()->setNumber(2);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->setBackup(0.0);
}

GoMarkovOperator18A::~GoMarkovOperator18A()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator18A::calcQualitativeProbability()
{
    DoubleVector IS1 = this->getPrevQualitativeStatus(0);
    DoubleVector IS2 = this->getPrevQualitativeStatus(1);
    DoubleVector IR = IS1 * IS2;
    this->_qualitativeOutput[0] = IR;
}

double GoMarkovOperator18A::backup() const
{
    return this->_backup;
}

void GoMarkovOperator18A::setBackup(double value)
{
    this->_backup = value;
}

void GoMarkovOperator18A::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GoMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    GoMarkovStatus *status2 = this->getPrevMarkovStatus(1);
    DoubleVector PS1 = status1->probabilityNormal();
    DoubleVector PS2 = status2->probabilityNormal();
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector muS1 = status1->frequencyRepair();
    DoubleVector muS2 = status2->frequencyRepair();
    DoubleVector P0 = PS1 * this->backup();
    DoubleVector PR = PS1 + PS2;
    if (PR > 1.0)
    {
        PR = 1.0;
    }
    DoubleVector muR = muS1 + muS2;
    DoubleVector lambdaR = (lambdaS1 * (PS1 - P0) + lambdaS1 * PS2) / PR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GoMarkovOperator18A::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    GoMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    GoMarkovStatus *status2 = this->getPrevMarkovStatus(1);
    DoubleVector PS1 = status1->probabilityNormal();
    DoubleVector PS2 = status2->probabilityNormal();
    DoubleVector lambdaS1 = status1->frequencyBreakdown();
    DoubleVector muS1 = status1->frequencyRepair();
    DoubleVector muS2 = status2->frequencyRepair();
    DoubleVector P0 = PS1 * this->backup();
    DoubleVector muR = muS1 + muS2;
    DoubleVector lambdaR = (lambdaS1 * (PS1 - P0) + lambdaS1 * PS2) / PR[0];
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GoMarkovOperator18A::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    DoubleVector PS1 = input[0];
    DoubleVector PS2 = input[1];
    DoubleVector PR = PS1 + PS2;
    if (PR > 1.0)
    {
        PR = 1.0;
    }
    return PR;
}

GoMarkovOperator* GoMarkovOperator18A::copy()
{
    GoMarkovOperator18A *op = (GoMarkovOperator18A*)this->GoMarkovOperator::copy();
    op->setBackup(this->backup());
    return op;
}

void GoMarkovOperator18A::save(QDomDocument &document, QDomElement &root)
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
    element.setAttribute("backup", this->backup());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->markovStatus3()->save(document, element);
    this->markovStatus4()->save(document, element);
}

bool GoMarkovOperator18A::tryOpen(QDomElement &root)
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
    return true;
}
