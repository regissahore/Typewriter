#include <cstdio>
#include <QObject>
#include <QPainter>
#include <qmath.h>
#include "gomarkovoperator.h"
#include "gomarkovstatus.h"
#include "goinput.h"
#include "gooutput.h"
#include "goparameter.h"
#include "gostatus.h"
#include "gosignal.h"
#include "messager.h"
#include "messagefactory.h"
#include "gomarkovoperatorfactory.h"
#include "rungekuttabreakdown3.h"
#include "rungekuttabreakdown4.h"

GOMarkovOperator::GOMarkovOperator() : GOOperator()
{
    this->_markovStatus = new GOMarkovStatus();
    this->_outputStatus = new QVector<GOMarkovStatus*>();
    this->setBreakdownNum(1);
    this->setBreakdownCorrelate(false);
    this->_markovStatus1 = new GOMarkovStatus();
    this->_markovStatus2 = new GOMarkovStatus();
    this->_markovStatus3 = new GOMarkovStatus();
    this->_markovStatus4 = new GOMarkovStatus();
    this->_rkBreakdown3 = new RungeKuttaBreakdown3();
    this->_rkBreakdown4 = new RungeKuttaBreakdown4();
    this->setIsGlobalFeedback(false);
}

GOMarkovOperator::~GOMarkovOperator()
{
    this->GOOperator::~GOOperator();
    delete this->_markovStatus;
    for (int i = 0; i < this->_outputStatus->size(); ++i)
    {
        delete this->_outputStatus->at(i);
    }
    delete this->_outputStatus;
    delete this->_markovStatus1;
    delete this->_markovStatus2;
    delete this->_markovStatus3;
    delete this->_markovStatus4;
    delete this->_rkBreakdown3;
    delete this->_rkBreakdown4;
}

int GOMarkovOperator::breakdownNum() const
{
    return this->_breakdownNum;
}

void GOMarkovOperator::setBreakdownNum(const int value)
{
    this->_breakdownNum = value;
}

GOMarkovStatus* GOMarkovOperator::markovStatus1() const
{
    return this->_markovStatus1;
}

GOMarkovStatus* GOMarkovOperator::markovStatus2() const
{
    return this->_markovStatus2;
}

GOMarkovStatus* GOMarkovOperator::markovStatus3() const
{
    return this->_markovStatus3;
}

GOMarkovStatus* GOMarkovOperator::markovStatus4() const
{
    return this->_markovStatus4;
}

bool GOMarkovOperator::isBreakdownCorrelate() const
{
    return this->_isBreakdownCorrelate;
}

void GOMarkovOperator::setBreakdownCorrelate(bool value)
{
    this->_isBreakdownCorrelate = value;
}

GOMarkovStatus* GOMarkovOperator::markovStatus() const
{
    return this->_markovStatus;
}

QVector<GOMarkovStatus*>* GOMarkovOperator::markovOutputStatus() const
{
    return this->_outputStatus;
}

void GOMarkovOperator::initMarkovStatus(double time, double c12)
{
    if (1 == this->breakdownNum())
    {
        double lambda = this->markovStatus1()->frequencyBreakdown();
        double mu = this->markovStatus1()->frequencyRepair();
        double PC = mu / (lambda + mu) * (1 + lambda / mu * exp(-(lambda + mu) * time)) + c12;
        this->markovStatus()->setProbabilityNormal(PC);
        this->markovStatus()->setFrequencyBreakdown(lambda);
        this->markovStatus()->setFrequencyRepair(mu);
    }
    else if (2 == this->breakdownNum())
    {
        double lambda1 = this->markovStatus1()->frequencyBreakdown();
        double mu1 = this->markovStatus1()->frequencyRepair();
        double lambda2 = this->markovStatus2()->frequencyBreakdown();
        double mu2 = this->markovStatus2()->frequencyRepair();
        double s1 = 0.5 * (-(lambda1 + lambda2 + mu1 + mu2) + sqrt((lambda1 - lambda2 + mu1 - mu2) * (lambda1 - lambda2 + mu1 - mu2) + 4 * lambda1 * lambda2));
        double s2 = 0.5 * (-(lambda1 + lambda2 + mu1 + mu2) - sqrt((lambda1 - lambda2 + mu1 - mu2) * (lambda1 - lambda2 + mu1 - mu2) + 4 * lambda1 * lambda2));
        double PC = mu1 * mu2 / s1 / s2 +
                (s1 * s1 + (mu1 + mu2) * s1 + mu1 * mu2) / (s1 * (s1 - s2)) * exp(s1 * time) +
                (s2 * s2 + (mu1 + mu2) * s2 + mu1 * mu2) / (s2 * (s2 - s1)) * exp(s2 * time) +
                c12;
        double QC = 1.0 - PC;
        double lambdaR = lambda1 + lambda2;
        double muR = lambdaR * PC / QC;
        this->markovStatus()->setProbabilityNormal(PC);
        this->markovStatus()->setFrequencyBreakdown(lambdaR);
        this->markovStatus()->setFrequencyRepair(muR);
    }
    else if (3 == this->breakdownNum())
    {
        double lambda1 = this->markovStatus1()->frequencyBreakdown();
        double lambda2 = this->markovStatus2()->frequencyBreakdown();
        double lambda3 = this->markovStatus3()->frequencyBreakdown();
        double mu1 = this->markovStatus1()->frequencyRepair();
        double mu2 = this->markovStatus2()->frequencyRepair();
        double mu3 = this->markovStatus3()->frequencyRepair();
        double PC = this->_rkBreakdown3->calcNormalProbability(time, lambda1, lambda2, lambda3, mu1, mu2, mu3);
        double P0 = this->_rkBreakdown3->rk0();
        double P1 = this->_rkBreakdown3->rk1();
        double P2 = this->_rkBreakdown3->rk2();
        double P3 = this->_rkBreakdown3->rk3();
        double lambda = lambda1 + lambda2 + lambda3;
        double mu = (mu1 * P1 + mu2 * P2 + mu3 * P3) / (1 - P0);
        this->markovStatus()->setProbabilityNormal(PC);
        this->markovStatus()->setFrequencyBreakdown(lambda);
        this->markovStatus()->setFrequencyRepair(mu);
    }
    else if (4 == this->breakdownNum())
    {
        double lambda1 = this->markovStatus1()->frequencyBreakdown();
        double lambda2 = this->markovStatus2()->frequencyBreakdown();
        double lambda3 = this->markovStatus3()->frequencyBreakdown();
        double lambda4 = this->markovStatus4()->frequencyBreakdown();
        double mu1 = this->markovStatus1()->frequencyRepair();
        double mu2 = this->markovStatus2()->frequencyRepair();
        double mu3 = this->markovStatus3()->frequencyRepair();
        double mu4 = this->markovStatus4()->frequencyRepair();
        double PC = this->_rkBreakdown4->calcNormalProbability(time, lambda1, lambda2, lambda3, lambda4, mu1, mu2, mu3, mu4);
        double P0 = this->_rkBreakdown4->rk0();
        double P1 = this->_rkBreakdown4->rk1();
        double P2 = this->_rkBreakdown4->rk2();
        double P3 = this->_rkBreakdown4->rk3();
        double P4 = this->_rkBreakdown4->rk4();
        double lambda = lambda1 + lambda2 + lambda3 + lambda4;
        double mu = (mu1 * P1 + mu2 * P2 + mu3 * P3 + mu4 * P4) / (1 - P0);
        this->markovStatus()->setProbabilityNormal(PC);
        this->markovStatus()->setFrequencyBreakdown(lambda);
        this->markovStatus()->setFrequencyRepair(mu);
    }
}

void GOMarkovOperator::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
}

void GOMarkovOperator::calcCommonOutputMarkovStatus(QVector<double> PR)
{
    Q_UNUSED(PR);
}

double GOMarkovOperator::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(input);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    return this->markovStatus()->probabilityNormal();
}

GOMarkovOperator* GOMarkovOperator::getPrevOperator(int index)
{
    GOSignal *signal = this->input()->signal()->at(index);
    return (GOMarkovOperator*)signal->next(this);
}

GOMarkovOperator* GOMarkovOperator::getPrevSubOperator(int index)
{
    GOSignal *signal = this->subInput()->signal()->at(index);
    return (GOMarkovOperator*)signal->next(this);
}

GOMarkovStatus* GOMarkovOperator::getPrevMarkovStatus(int index)
{
    GOSignal *signal = this->input()->signal()->at(index);
    GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(this);
    int prevIndex = prev->output()->getSignalIndex(signal);
    GOMarkovStatus *status = prev->markovOutputStatus()->at(prevIndex);
    return status;
}

GOMarkovStatus* GOMarkovOperator::getPrevSubMarkovStatus(int index)
{
    GOSignal *signal = this->subInput()->signal()->at(index);
    GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(this);
    int prevIndex = prev->output()->getSignalIndex(signal);
    GOMarkovStatus *status = prev->markovOutputStatus()->at(prevIndex);
    return status;
}

void GOMarkovOperator::initOutputMarkovStatus()
{
    for (int i = this->_outputStatus->size(); i < this->output()->number(); ++i)
    {
        this->_outputStatus->push_back(new GOMarkovStatus());
    }
}

bool GOMarkovOperator::errorDetect(Messager *messager)
{
    bool flag = false;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        if (this->input()->signal()->at(i) == 0)
        {
            flag = true;
            Message *message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_ERROR);
            message->paramString = QObject::tr("Error: Operator ") + GOMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 does not have input at %2.").arg(this->id()).arg(i + 1);
            messager->sendMessage(message);
        }
    }
    for (int i = 0; i < this->subInput()->number(); ++i)
    {
        if (this->subInput()->signal()->at(i) == 0)
        {
            flag = true;
            Message *message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_ERROR);
            message->paramString = QObject::tr("Error: Operator ") + GOMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 does not have sub input at %2.").arg(this->id()).arg(i + 1);
            messager->sendMessage(message);
        }
    }
    return flag;
}

bool GOMarkovOperator::isGlobalFeedback() const
{
    return this->_isGlobalFeedback;
}

void GOMarkovOperator::setIsGlobalFeedback(const bool value)
{
    this->_isGlobalFeedback = value;
}

GOMarkovOperator* GOMarkovOperator::copy()
{
    GOMarkovOperator *op = GOMarkovOperatorFactory::produce(this->TypedItem::type());
    op->setId(this->id());
    op->setType(this->TypedItem::type());
    op->input()->setNumber(this->input()->number());
    op->subInput()->setNumber(this->subInput()->number());
    op->output()->setNumber(this->output()->number());

    op->setBreakdownNum(this->breakdownNum());
    op->setBreakdownCorrelate(this->isBreakdownCorrelate());
    op->setIsGlobalFeedback(this->isGlobalFeedback());

    op->markovStatus()->setProbabilityNormal(this->markovStatus()->probabilityNormal());
    op->markovStatus()->setFrequencyBreakdown(this->markovStatus()->frequencyBreakdown());
    op->markovStatus()->setFrequencyRepair(this->markovStatus()->frequencyRepair());

    op->markovStatus1()->setProbabilityNormal(this->markovStatus1()->probabilityNormal());
    op->markovStatus1()->setFrequencyBreakdown(this->markovStatus1()->frequencyBreakdown());
    op->markovStatus1()->setFrequencyRepair(this->markovStatus1()->frequencyRepair());

    op->markovStatus2()->setProbabilityNormal(this->markovStatus2()->probabilityNormal());
    op->markovStatus2()->setFrequencyBreakdown(this->markovStatus2()->frequencyBreakdown());
    op->markovStatus2()->setFrequencyRepair(this->markovStatus2()->frequencyRepair());

    op->markovStatus3()->setProbabilityNormal(this->markovStatus3()->probabilityNormal());
    op->markovStatus3()->setFrequencyBreakdown(this->markovStatus3()->frequencyBreakdown());
    op->markovStatus3()->setFrequencyRepair(this->markovStatus3()->frequencyRepair());

    op->markovStatus4()->setProbabilityNormal(this->markovStatus4()->probabilityNormal());
    op->markovStatus4()->setFrequencyBreakdown(this->markovStatus4()->frequencyBreakdown());
    op->markovStatus4()->setFrequencyRepair(this->markovStatus4()->frequencyRepair());
    return op;
}

void GOMarkovOperator::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    element.setAttribute("dual", this->breakdownNum());
    element.setAttribute("breakdown", this->isBreakdownCorrelate());
    element.setAttribute("global_feedback", this->isGlobalFeedback());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->markovStatus3()->save(document, element);
    this->markovStatus4()->save(document, element);
}

bool GOMarkovOperator::tryOpen(QDomElement &root)
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
    this->setBreakdownNum(root.attribute("dual").toInt());
    this->setBreakdownCorrelate(root.attribute("breakdown").toInt());
    this->setIsGlobalFeedback(root.attribute("global_feedback", "0").toInt());
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

void GOMarkovOperator::paintParameter(QPainter *painter)
{
    if (!GOMarkovOperatorFactory::isLogical(this->TypedItem::type()))
    {
        this->paintMarkovParameter(painter);
    }
}

void GOMarkovOperator::paintMarkovParameter(QPainter *painter)
{
    int y = 30;
    if (this->breakdownNum() > 0)
    {
        painter->drawText(-50, y, QObject::tr("Lambda 1: %1").arg(this->_markovStatus1->frequencyBreakdown()));
        painter->drawText(-50, y + 20, QObject::tr("    Mu 1: %1").arg(this->_markovStatus1->frequencyRepair()));
    }
    y += 40;
    if (this->breakdownNum() > 1)
    {
        painter->drawText(-50, y, QObject::tr("Lambda 2: %1").arg(this->_markovStatus2->frequencyBreakdown()));
        painter->drawText(-50, y + 20, QObject::tr("    Mu 2: %1").arg(this->_markovStatus2->frequencyRepair()));
    }
    y += 40;
    if (this->breakdownNum() > 2)
    {
        painter->drawText(-50, y, QObject::tr("Lambda 3: %1").arg(this->_markovStatus3->frequencyBreakdown()));
        painter->drawText(-50, y + 20, QObject::tr("    Mu 3: %1").arg(this->_markovStatus3->frequencyRepair()));
    }
    y += 40;
    if (this->breakdownNum() > 3)
    {
        painter->drawText(-50, y, QObject::tr("Lambda 4: %1").arg(this->_markovStatus4->frequencyBreakdown()));
        painter->drawText(-50, y + 20, QObject::tr("    Mu 4: %1").arg(this->_markovStatus4->frequencyRepair()));
    }
}
