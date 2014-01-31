#include <QObject>
#include <QPainter>
#include <qmath.h>
#include "GoMarkovOperator19.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"
#include "Messager.h"
#include "MessageFactory.h"
#include "GoMarkovOperatorFactory.h"

GoMarkovOperator19::GoMarkovOperator19() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(2);
    this->_deltaNum = 2;
    this->_delta = new QVector<double>();
}

GoMarkovOperator19::~GoMarkovOperator19()
{
    this->GoMarkovOperator::~GoMarkovOperator();
    this->_delta->clear();
    delete this->_delta;
}

void GoMarkovOperator19::calcQualitativeProbability()
{
    DoubleVector IS = this->getPrevQualitativeStatus();
    DoubleVector IC = this->getPrevSubQualitativeStatus();
    DoubleVector IR1 = IS * IC;
    DoubleVector IR2 = IS * IC;
    this->_qualitativeOutput[0] = IR1;
    this->_qualitativeOutput[1] = IR2;
}

QVector<double>* GoMarkovOperator19::delta() const
{
    return this->_delta;
}

int GoMarkovOperator19::deltaNum() const
{
    return this->_deltaNum;
}

void GoMarkovOperator19::setDeltaNum(int value)
{
    this->_deltaNum = value;
    while (this->delta()->size() < value - 2)
    {
        this->delta()->push_back(0.0);
    }
}

void GoMarkovOperator19::calcOutputMarkovStatus(double time)
{
    DoubleVector deltaSum = 0.0;
    for (int i = 0; i < this->delta()->size(); ++i)
    {
        deltaSum = deltaSum + this->delta()->at(i);
    }
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector muC = this->markovStatus()->frequencyRepair();
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    if (this->breakdownNum() == 1)
    {
        PC = muC / (muC + lambdaC) + lambdaC / (lambdaC + muC) * DoubleVector::Exp(- (lambdaC + muC) * time);
    }
    DoubleVector PS = this->getPrevMarkovStatus()->probabilityNormal();
    DoubleVector lambdaS = this->getPrevMarkovStatus()->frequencyBreakdown();
    DoubleVector PS1 = PS;
    DoubleVector PSi = (1.0 - PS) * deltaSum;
    DoubleVector PR1 = PS1 + PSi * PC;
    DoubleVector QR1 = 1.0 - PR1;
    DoubleVector lambdaR1 = lambdaS + lambdaC;
    if (this->deltaNum() == 2)
    {
        lambdaR1 = lambdaS;
    }
    DoubleVector muR1 = lambdaR1 * PR1 / QR1;
    DoubleVector PR2 = (PS1 + PSi) * PC;
    if (this->deltaNum() == 2)
    {
        PR2 = PS1 * PC;
    }
    DoubleVector QR2 = 1.0 - PR2;
    DoubleVector lambdaR2 = lambdaS + lambdaC;
    DoubleVector muR2 = lambdaR2 * PR2 / QR2;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR1);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR1);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR1);
    this->markovOutputStatus()->at(1)->setProbabilityNormal(PR2);
    this->markovOutputStatus()->at(1)->setFrequencyBreakdown(lambdaR2);
    this->markovOutputStatus()->at(1)->setFrequencyRepair(muR2);
}

DoubleVector GoMarkovOperator19::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    DoubleVector deltaSum = 0.0;
    for (int i = 0; i < this->delta()->size(); ++i)
    {
        deltaSum = deltaSum + this->delta()->at(i);
    }
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    DoubleVector muC = this->markovStatus()->frequencyRepair();
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    if (this->breakdownNum() == 1)
    {
        PC = muC / (muC + lambdaC) + lambdaC / (lambdaC + muC) * DoubleVector::Exp(- (lambdaC + muC) * time);
    }
    DoubleVector PS = input[0];
    DoubleVector PS1 = PS;
    DoubleVector PSi = (1.0 - PS) * deltaSum;
    DoubleVector PR1 = PS1 + PSi * PC;
    DoubleVector PR2 = (PS1 + PSi) * PC;
    if (this->deltaNum() == 2)
    {
        PR2 = PS1 * PC;
    }
    if (index == 0)
    {
        return PR1;
    }
    return PR2;
}

void GoMarkovOperator19::paintParameter(QPainter *painter)
{
    int y = 40;
    if (this->breakdownNum() > 0)
    {
        painter->drawText(-50, y, QObject::tr("Lambda 1: %1").arg(this->_markovStatus1->frequencyBreakdown().getValue(0)));
        painter->drawText(-50, y + 20, QObject::tr("    Mu 1: %1").arg(this->_markovStatus1->frequencyRepair().getValue(0)));
        y += 40;
    }
    if (this->breakdownNum() > 1)
    {
        painter->drawText(-50, y, QObject::tr("Lambda 2: %1").arg(this->_markovStatus2->frequencyBreakdown().getValue(0)));
        painter->drawText(-50, y + 20, QObject::tr("    Mu 2: %1").arg(this->_markovStatus2->frequencyRepair().getValue(0)));
        y += 40;
    }
    if (this->breakdownNum() > 2)
    {
        painter->drawText(-50, y, QObject::tr("Lambda 3: %1").arg(this->_markovStatus3->frequencyBreakdown().getValue(0)));
        painter->drawText(-50, y + 20, QObject::tr("    Mu 3: %1").arg(this->_markovStatus3->frequencyRepair().getValue(0)));
        y += 40;
    }
    if (this->breakdownNum() > 3)
    {
        painter->drawText(-50, y, QObject::tr("Lambda 4: %1").arg(this->_markovStatus4->frequencyBreakdown().getValue(0)));
        painter->drawText(-50, y + 20, QObject::tr("    Mu 4: %1").arg(this->_markovStatus4->frequencyRepair().getValue(0)));
        y += 40;
    }
}

GoMarkovOperator* GoMarkovOperator19::copy()
{
    GoMarkovOperator19 *op = (GoMarkovOperator19*)this->GoMarkovOperator::copy();
    op->setDeltaNum(this->deltaNum());
    for (int i = 0; i < this->deltaNum(); ++i)
    {
        op->delta()->push_back(this->delta()->at(i));
    }
    return op;
}

void GoMarkovOperator19::save(QDomDocument &document, QDomElement &root)
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
    element.setAttribute("delta", this->deltaNum());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->markovStatus3()->save(document, element);
    this->markovStatus4()->save(document, element);
    QDomElement subElement = document.createElement("markov2");
    for (int i = 0; i < this->deltaNum() - 2; ++i)
    {
        QDomElement node = document.createElement("node");
        node.setAttribute("delta", this->delta()->at(i));
        subElement.appendChild(node);
    }
    element.appendChild(subElement);
}

bool GoMarkovOperator19::tryOpen(QDomElement &root)
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
    this->delta()->clear();
    for (int i = 0; i < this->deltaNum() - 2; ++i)
    {
        this->delta()->push_back(node.attribute("delta").toDouble());
        node = node.nextSiblingElement();
    }
    return true;
}
