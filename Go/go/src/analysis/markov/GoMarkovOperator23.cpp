#include <qmath.h>
#include "GoMarkovOperator23.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator23::GoMarkovOperator23() : GoMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->_alpha = new QVector<double>();
}

GoMarkovOperator23::~GoMarkovOperator23()
{
    this->GoMarkovOperator::~GoMarkovOperator();
    this->_alpha->clear();
    delete this->_alpha;
}

void GoMarkovOperator23::calcQualitativeProbability()
{
    DoubleVector IR = 1.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        DoubleVector IS = this->getPrevQualitativeStatus(i);
        IR = IR * IS;
    }
    this->_qualitativeOutput[0] = IR;
}

QVector<double>* GoMarkovOperator23::alpha() const
{
    return this->_alpha;
}

void GoMarkovOperator23::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    DoubleVector PR = 0.0;
    DoubleVector lambdaR = 0.0;
    DoubleVector muR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *status = this->getPrevMarkovStatus(i);
        DoubleVector PS = status->probabilityNormal();
        DoubleVector lambdaS = status->frequencyBreakdown();
        DoubleVector muS = status->frequencyRepair();
        PR += PS * this->alpha()->at(i);
        lambdaR += lambdaS * this->alpha()->at(i);
        muR += muS * this->alpha()->at(i);
    }
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GoMarkovOperator23::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    DoubleVector lambdaR = 0.0;
    DoubleVector muR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *status = this->getPrevMarkovStatus(i);
        DoubleVector lambdaS = status->frequencyBreakdown();
        DoubleVector muS = status->frequencyRepair();
        lambdaR += lambdaS * this->alpha()->at(i);
        muR += muS * this->alpha()->at(i);
    }
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GoMarkovOperator23::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    DoubleVector PR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        DoubleVector PS = input[i];
        PR += PS * this->alpha()->at(i);
    }
    return PR;
}

GoMarkovOperator* GoMarkovOperator23::copy()
{
    GoMarkovOperator23 *op = (GoMarkovOperator23*)this->GoMarkovOperator::copy();
    for (int i = 0; i < this->input()->number(); ++i)
    {
        op->alpha()->push_back(this->alpha()->at(i));
    }
    return op;
}

void GoMarkovOperator23::save(QDomDocument &document, QDomElement &root)
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
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->markovStatus3()->save(document, element);
    this->markovStatus4()->save(document, element);
    QDomElement subElement = document.createElement("markov2");
    for (int i = 0; i < this->input()->number(); ++i)
    {
        QDomElement node = document.createElement("node");
        node.setAttribute("alpha", this->alpha()->at(i));
        subElement.appendChild(node);
    }
    element.appendChild(subElement);
}

bool GoMarkovOperator23::tryOpen(QDomElement &root)
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
    for (int i = 0; i < this->input()->number(); ++i)
    {
        this->alpha()->push_back(node.attribute("alpha").toDouble());
        node = node.nextSiblingElement();
    }
    return true;
}
