#include <QObject>
#include <QPainter>
#include <qmath.h>
#include <algorithm>
#include "GoMarkovOperator12a.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"
#include "Messager.h"
#include "MessageFactory.h"
#include "GoMarkovOperatorFactory.h"
using namespace std;

GoMarkovOperator12A::GoMarkovOperator12A() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(3);
    this->setIsUseDelta(false);
    this->_deltaNum = 1;
    this->_ids = new QVector<QString>();
    this->_delta = new QVector<double>();
    this->_ids->push_back("0");
    this->_delta->push_back(0.0);
}

GoMarkovOperator12A::~GoMarkovOperator12A()
{
    this->GoMarkovOperator::~GoMarkovOperator();
    this->_ids->clear();
    delete this->_ids;
    this->_delta->clear();
    delete this->_delta;
}

void GoMarkovOperator12A::calcQualitativeProbability()
{
    DoubleVector IS = this->getPrevQualitativeStatus();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        this->_qualitativeOutput[i] = IS.getValue(i);
    }
}

void GoMarkovOperator12A::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GoMarkovStatus *prevStatus = this->getPrevMarkovStatus();
    DoubleVector PR = prevStatus->probabilityNormal();
    DoubleVector lambdaR = prevStatus->frequencyBreakdown();
    DoubleVector muR = prevStatus->frequencyRepair();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR.getValue(i));
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR.getValue(i));
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR.getValue(i));
    }
}

DoubleVector GoMarkovOperator12A::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    return input[0].getValue(index);
}

QVector<QString>* GoMarkovOperator12A::ids() const
{
    return this->_ids;
}

QVector<double>* GoMarkovOperator12A::delta() const
{
    return this->_delta;
}

bool GoMarkovOperator12A::isUseDelta() const
{
    return this->_isUseDelta;
}

void GoMarkovOperator12A::setIsUseDelta(const bool value)
{
    this->_isUseDelta = value;
    if (value)
    {
        this->setDeltaNum(this->output()->number() - 1);
    }
}

int GoMarkovOperator12A::deltaNum() const
{
    return this->_deltaNum;
}

void GoMarkovOperator12A::setDeltaNum(int value)
{
    this->_deltaNum = value;
    for (int i = this->_delta->size(); i < value; ++i)
    {
        this->_ids->push_back("0");
        this->_delta->push_back(0.0);
    }
}

double fun12a(double P, double lambda, double mu, double t)
{
    return ( mu / (lambda + mu) ) * (1 + lambda / mu * exp( - (lambda + mu) * t ) ) - P;
}

double fun12a_(double lambda, double mu, double t)
{
    return (- mu / ( (lambda + mu) * (lambda + mu) ) ) * (1.0 + lambda / mu * exp( - (lambda + mu) * t ) ) +
            ( mu / (lambda + mu) ) * ( ( 1.0 / mu ) * exp( - (lambda + mu) * t ) +
                                       ( lambda / mu) * ( - t * exp( - (lambda + mu) * t ) ) );
}

double newton12a(double P, double mu, double t)
{
    double prev = 0.0;
    while (true)
    {
        double cur = prev - fun12a(P, prev, mu, t) / fun12a_(prev, mu, t);
        if (isinf(cur) || isnan(cur))
        {
            return cur;
        }
        if (fabs(prev - cur) < 1e-10)
        {
            return prev;
        }
        prev = cur;
    }
}

void GoMarkovOperator12A::calcOutputMarkovStatus(QVector<GoMarkovStatus> prevStatus, double time)
{
    if (prevStatus.size() > 0)
    {
        DoubleVector mu = prevStatus[0].frequencyRepair();
        for (int i = 0; i < this->output()->number(); ++i)
        {
            DoubleVector PR = prevStatus[i].probabilityNormal();
            DoubleVector muR = mu;
            DoubleVector lambdaR = prevStatus[i].frequencyBreakdown();
            for (int j = 0; j < prevStatus[i].frequencyBreakdown().length(); ++j)
            {
                lambdaR.setValue(j, newton12a(PR.getValue(j), muR.getValue(j), time));
            }
            this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
            this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
            this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
        }
    }
}

void GoMarkovOperator12A::paintParameter(QPainter *painter)
{
    int y = 40;
    if (this->isUseDelta())
    {
        painter->drawText(-50, y, QObject::tr("Relvent"));
        for (int i = 0; i < this->deltaNum(); ++i)
        {
            y += 20;
            painter->drawText(-50, y, QString("%1: %2").arg(this->ids()->at(i)).arg(this->delta()->at(i)));
        }
    }
}

GoMarkovOperator* GoMarkovOperator12A::copy()
{
    GoMarkovOperator12A *op = (GoMarkovOperator12A*)this->GoMarkovOperator::copy();
    op->setIsUseDelta(this->isUseDelta());
    op->setDeltaNum(this->deltaNum());
    return op;
}

void GoMarkovOperator12A::save(QDomDocument &document, QDomElement &root)
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
    element.setAttribute("use_delta", this->isUseDelta());
    element.setAttribute("delta", this->deltaNum());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->markovStatus3()->save(document, element);
    this->markovStatus4()->save(document, element);
    QDomElement subElement = document.createElement("markov2");
    for (int i = 0; i < this->deltaNum(); ++i)
    {
        QDomElement node = document.createElement("node");
        node.setAttribute("a", this->ids()->at(i));
        node.setAttribute("delta", this->delta()->at(i));
        subElement.appendChild(node);
    }
    element.appendChild(subElement);
}

bool GoMarkovOperator12A::tryOpen(QDomElement &root)
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
    this->setIsUseDelta(root.attribute("use_delta").toInt());
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
    this->ids()->clear();
    this->delta()->clear();
    for (int i = 0; i < this->deltaNum(); ++i)
    {
        this->ids()->push_back(node.attribute("a"));
        this->delta()->push_back(node.attribute("delta").toDouble());
        node = node.nextSiblingElement();
    }
    return true;
}
