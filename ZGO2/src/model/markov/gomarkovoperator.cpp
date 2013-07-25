#include <cstdio>
#include <QObject>
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

GOMarkovOperator::GOMarkovOperator() : GOOperator()
{
    this->_markovStatus = new GOMarkovStatus();
    this->_outputStatus = new QVector<GOMarkovStatus*>();
    this->setDualBreakdown(false);
    this->setBreakdownCorrelate(false);
    this->_markovStatus1 = new GOMarkovStatus();
    this->_markovStatus2 = new GOMarkovStatus();
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
}

bool GOMarkovOperator::isDualBreakdown() const
{
    return this->_isDualBreakdown;
}

void GOMarkovOperator::setDualBreakdown(bool value)
{
    this->_isDualBreakdown = value;
}

GOMarkovStatus* GOMarkovOperator::markovStatus1() const
{
    return this->_markovStatus1;
}

GOMarkovStatus* GOMarkovOperator::markovStatus2() const
{
    return this->_markovStatus2;
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
    if (this->isDualBreakdown())
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
    else
    {
        double lambda = this->markovStatus()->frequencyBreakdown();
        double mu = this->markovStatus()->frequencyRepair();
        double PC = mu / (lambda + mu) * (1 + lambda / mu * exp(-(lambda + mu) * time)) + c12;
        this->markovStatus()->setProbabilityNormal(PC);
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

GOMarkovOperator* GOMarkovOperator::copy()
{
    GOMarkovOperator *op = GOMarkovOperatorFactory::produce(this->TypedItem::type());
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
    element.setAttribute("dual", this->isDualBreakdown());
    element.setAttribute("breakdown", this->isBreakdownCorrelate());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
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
    if (!this->markovStatus1()->tryOpen(element))
    {
        return false;
    }
    if (!this->markovStatus2()->tryOpen(element))
    {
        return false;
    }
    return true;
}
