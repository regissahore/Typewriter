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
    this->_deltaNum = 1;
    this->_ids = new QVector<QString>();
    this->_delta = new QVector<double>();
    this->_ids->push_back("0");
    this->_delta->push_back(0.0);
}

GoMarkovOperator19::~GoMarkovOperator19()
{
    this->GoMarkovOperator::~GoMarkovOperator();
    this->_ids->clear();
    delete this->_ids;
    this->_delta->clear();
    delete this->_delta;
}

QVector<QString> *GoMarkovOperator19::ids() const
{
    return this->_ids;
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
}

double fun(double P, double lambda, double mu, double t)
{
    return ( mu / (lambda + mu) ) * (1 + lambda / mu * exp( - (lambda + mu) * t ) ) - P;
}

double fun_(double lambda, double mu, double t)
{
    return (- mu / ( (lambda + mu) * (lambda + mu) ) ) * (1.0 + lambda / mu * exp( - (lambda + mu) * t ) ) +
            ( mu / (lambda + mu) ) * ( ( 1.0 / mu ) * exp( - (lambda + mu) * t ) +
                                       ( lambda / mu) * ( - t * exp( - (lambda + mu) * t ) ) );
}

double newton(double P, double mu, double t)
{
    double prev = 0.0;
    while (true)
    {
        double cur = prev - fun(P, prev, mu, t) / fun_(prev, mu, t);
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

void GoMarkovOperator19::calcOutputMarkovStatus(GoMarkovStatus prevStatus, double time)
{
    DoubleVector PS = prevStatus.probabilityNormal();
    DoubleVector lambdaS = prevStatus.frequencyBreakdown();
    DoubleVector muS = prevStatus.frequencyRepair();
    for (int i = 0; i < lambdaS.length(); ++i)
    {
        lambdaS.setValue(i, newton(PS.getValue(i), muS.getValue(0), time));
    }
    DoubleVector PR2(0.0);
    DoubleVector lambdaR2(0.0);
    DoubleVector muR2(0.0);
    DoubleVector PC = this->markovStatus()->probabilityNormal();
    DoubleVector lambdaC = this->markovStatus()->frequencyBreakdown();
    for (int i = 1; i <= this->deltaNum(); ++i)
    {
        PR2 += PS.getValue(i) * PC;
        lambdaR2 += (lambdaS.getValue(i) + lambdaC) * PS.getValue(i) * PC;
        muR2 += lambdaS.getValue(i) + lambdaC;
    }
    DoubleVector PR1 = PS.getValue(0) + PR2;
    DoubleVector lambdaR1 = lambdaS.getValue(0) * PS.getValue(0) + lambdaR2;
    lambdaR1 /= PR1;
    lambdaR2 /= PR2;
    DoubleVector QR2 = 1.0 - PR2;
    muR2 = muR2 * PR2 / QR2;
    DoubleVector muR1 = muS + muR2;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR1);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR1);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR1);
    this->markovOutputStatus()->at(1)->setProbabilityNormal(PR2);
    this->markovOutputStatus()->at(1)->setFrequencyBreakdown(lambdaR2);
    this->markovOutputStatus()->at(1)->setFrequencyRepair(muR2);
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
    painter->drawText(-50, y, QObject::tr("Relvent"));
    for (int i = 0; i < this->deltaNum(); ++i)
    {
        y += 20;
        painter->drawText(-50, y, QString("%1: %2").arg(this->ids()->at(i)).arg(this->delta()->at(i)));
    }
}

GoMarkovOperator* GoMarkovOperator19::copy()
{
    GoMarkovOperator19 *op = (GoMarkovOperator19*)this->GoMarkovOperator::copy();
    op->setDeltaNum(this->deltaNum());
    for (int i = 0; i < this->deltaNum(); ++i)
    {
        op->ids()->push_back(this->ids()->at(i));
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
    for (int i = 0; i < this->deltaNum(); ++i)
    {
        QDomElement node = document.createElement("node");
        node.setAttribute("a", this->ids()->at(i));
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
