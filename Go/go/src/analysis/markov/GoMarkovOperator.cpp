#include <cstdio>
#include <QObject>
#include <QPainter>
#include <qmath.h>
#include "GoMarkovOperator.h"
#include "GoMarkovStatus.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoParameter.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "Messager.h"
#include "MessageFactory.h"
#include "GoMarkovOperatorFactory.h"
#include "RungeKuttaBreakdown2.h"
#include "RungeKuttaBreakdown3.h"
#include "RungeKuttaBreakdown4.h"

GoMarkovOperator::GoMarkovOperator() : GoOperator()
{
    this->_markovStatus = new GoMarkovStatus();
    this->_outputStatus = new QVector<GoMarkovStatus*>();
    this->setBreakdownNum(1);
    this->setBreakdownCorrelate(false);
    this->_markovStatus1 = new GoMarkovStatus();
    this->_markovStatus2 = new GoMarkovStatus();
    this->_markovStatus3 = new GoMarkovStatus();
    this->_markovStatus4 = new GoMarkovStatus();
    this->_rkBreakdown2 = new RungeKuttaBreakdown2();
    this->_rkBreakdown3 = new RungeKuttaBreakdown3();
    this->_rkBreakdown4 = new RungeKuttaBreakdown4();
    this->setIsGlobalFeedback(false);
    this->_error = "";
}

GoMarkovOperator::~GoMarkovOperator()
{
    this->GoOperator::~GoOperator();
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

DoubleVector GoMarkovOperator::qualitativeStatus()
{
    return this->_qualitativeStatus;
}

QVector<DoubleVector> *GoMarkovOperator::qualitativeOutput()
{
    return &this->_qualitativeOutput;
}

void GoMarkovOperator::setQualitativeStatus(DoubleVector value)
{
    this->_qualitativeStatus = value;
}

void GoMarkovOperator::setQualitativeOutput(int index, DoubleVector value)
{
    this->_qualitativeOutput[index] = value;
}

DoubleVector GoMarkovOperator::getPrevQualitativeStatus(int index)
{
    GoSignal *signal = this->input()->signal()->at(index);
    GoMarkovOperator *prev = (GoMarkovOperator*)signal->next(this);
    int prevIndex = prev->output()->getSignalIndex(signal);
    return prev->qualitativeOutput()->at(prevIndex);
}

DoubleVector GoMarkovOperator::getPrevSubQualitativeStatus(int index)
{
    GoSignal *signal = this->subInput()->signal()->at(index);
    GoMarkovOperator *prev = (GoMarkovOperator*)signal->next(this);
    int prevIndex = prev->output()->getSignalIndex(signal);
    return prev->qualitativeOutput()->at(prevIndex);
}

void GoMarkovOperator::initQualitativeOutput()
{
    this->qualitativeOutput()->clear();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        this->qualitativeOutput()->push_back(0.0);
    }
}

void GoMarkovOperator::calcQualitativeProbability()
{
    if (GoMarkovOperatorFactory::isLogical(this->type()))
    {
        DoubleVector IS = this->getPrevQualitativeStatus();
        DoubleVector IR = IS;
        this->_qualitativeOutput[0] = IR;
    }
    else
    {
        DoubleVector IS = this->getPrevQualitativeStatus();
        DoubleVector IC = this->qualitativeStatus();
        DoubleVector IR = IS * IC;
        this->_qualitativeOutput[0] = IR;
    }
}

int GoMarkovOperator::breakdownNum() const
{
    return this->_breakdownNum;
}

void GoMarkovOperator::setBreakdownNum(const int value)
{
    this->_breakdownNum = value;
}

GoMarkovStatus* GoMarkovOperator::markovStatus1() const
{
    return this->_markovStatus1;
}

GoMarkovStatus* GoMarkovOperator::markovStatus2() const
{
    return this->_markovStatus2;
}

GoMarkovStatus* GoMarkovOperator::markovStatus3() const
{
    return this->_markovStatus3;
}

GoMarkovStatus* GoMarkovOperator::markovStatus4() const
{
    return this->_markovStatus4;
}

bool GoMarkovOperator::isBreakdownCorrelate() const
{
    return this->_isBreakdownCorrelate;
}

void GoMarkovOperator::setBreakdownCorrelate(bool value)
{
    this->_isBreakdownCorrelate = value;
}

GoMarkovStatus* GoMarkovOperator::markovStatus() const
{
    return this->_markovStatus;
}

QVector<GoMarkovStatus*>* GoMarkovOperator::markovOutputStatus() const
{
    return this->_outputStatus;
}

void GoMarkovOperator::initWithCurrentLambda(double time)
{
    DoubleVector lambda = this->markovStatus()->frequencyBreakdown();
    DoubleVector mu = this->markovStatus()->frequencyRepair();
    DoubleVector PC = mu / (lambda + mu) * (1.0 + lambda / mu * DoubleVector::Exp(- (lambda + mu) * time));
    this->markovStatus()->setProbabilityNormal(PC);
}

void GoMarkovOperator::initMarkovStatus(double time, double c12)
{
    if (1 == this->breakdownNum())
    {
        DoubleVector lambda = this->markovStatus1()->frequencyBreakdown();
        DoubleVector mu = this->markovStatus1()->frequencyRepair();
        DoubleVector PC = mu / (lambda + mu) * (1.0 + lambda / mu * DoubleVector::Exp(- (lambda + mu) * time)) + c12;
        mu = lambda * PC / (1.0 - PC);
        this->markovStatus()->setProbabilityNormal(PC);
        this->markovStatus()->setFrequencyBreakdown(lambda);
        this->markovStatus()->setFrequencyRepair(mu);
    }
    else if (2 == this->breakdownNum())
    {
        DoubleVector lambda1 = this->markovStatus1()->frequencyBreakdown();
        DoubleVector lambda2 = this->markovStatus2()->frequencyBreakdown();
        DoubleVector P0 = this->_rkBreakdown2->getY(0) + c12;
        DoubleVector lambda = lambda1 + lambda2;
        DoubleVector mu = lambda * P0 / (1.0 - P0);
        this->markovStatus()->setProbabilityNormal(P0);
        this->markovStatus()->setFrequencyBreakdown(lambda);
        this->markovStatus()->setFrequencyRepair(mu);
    }
    else if (3 == this->breakdownNum())
    {
        DoubleVector lambda1 = this->markovStatus1()->frequencyBreakdown();
        DoubleVector lambda2 = this->markovStatus2()->frequencyBreakdown();
        DoubleVector lambda3 = this->markovStatus3()->frequencyBreakdown();
        DoubleVector P0 = this->_rkBreakdown3->getY(0) + c12;
        DoubleVector lambda = lambda1 + lambda2 + lambda3;
        DoubleVector mu = lambda * P0 / (1.0 - P0);
        this->markovStatus()->setProbabilityNormal(P0);
        this->markovStatus()->setFrequencyBreakdown(lambda);
        this->markovStatus()->setFrequencyRepair(mu);
    }
    else if (4 == this->breakdownNum())
    {
        DoubleVector lambda1 = this->markovStatus1()->frequencyBreakdown();
        DoubleVector lambda2 = this->markovStatus2()->frequencyBreakdown();
        DoubleVector lambda3 = this->markovStatus3()->frequencyBreakdown();
        DoubleVector lambda4 = this->markovStatus4()->frequencyBreakdown();
        DoubleVector P0 = this->_rkBreakdown4->getY(0) + c12;
        DoubleVector lambda = lambda1 + lambda2 + lambda3 + lambda4;
        DoubleVector mu = lambda * P0 / (1.0 - P0);
        this->markovStatus()->setProbabilityNormal(P0);
        this->markovStatus()->setFrequencyBreakdown(lambda);
        this->markovStatus()->setFrequencyRepair(mu);
    }
}

void GoMarkovOperator::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
}

void GoMarkovOperator::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    Q_UNUSED(PR);
}

DoubleVector GoMarkovOperator::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(input);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    return this->markovStatus()->probabilityNormal();
}

GoMarkovOperator* GoMarkovOperator::getPrevOperator(int index)
{
    GoSignal *signal = this->input()->signal()->at(index);
    return (GoMarkovOperator*)signal->next(this);
}

GoMarkovOperator* GoMarkovOperator::getPrevSubOperator(int index)
{
    GoSignal *signal = this->subInput()->signal()->at(index);
    return (GoMarkovOperator*)signal->next(this);
}

int GoMarkovOperator::getPrevIndex(int index)
{
    GoSignal *signal = this->input()->signal()->at(index);
    GoMarkovOperator *op = (GoMarkovOperator*)signal->next(this);
    return op->output()->getSignalIndex(signal);
}

int GoMarkovOperator::getPrevSubIndex(int index)
{
    GoSignal *signal = this->subInput()->signal()->at(index);
    GoMarkovOperator *op = (GoMarkovOperator*)signal->next(this);
    return op->output()->getSignalIndex(signal);
}

GoMarkovStatus* GoMarkovOperator::getPrevMarkovStatus(int index)
{
    GoSignal *signal = this->input()->signal()->at(index);
    GoMarkovOperator *prev = (GoMarkovOperator*)signal->next(this);
    int prevIndex = prev->output()->getSignalIndex(signal);
    GoMarkovStatus *status = prev->markovOutputStatus()->at(prevIndex);
    return status;
}

GoMarkovStatus* GoMarkovOperator::getPrevSubMarkovStatus(int index)
{
    GoSignal *signal = this->subInput()->signal()->at(index);
    GoMarkovOperator *prev = (GoMarkovOperator*)signal->next(this);
    int prevIndex = prev->output()->getSignalIndex(signal);
    GoMarkovStatus *status = prev->markovOutputStatus()->at(prevIndex);
    return status;
}

void GoMarkovOperator::initOutputMarkovStatus()
{
    for (int i = this->_outputStatus->size(); i < this->output()->number(); ++i)
    {
        this->_outputStatus->push_back(new GoMarkovStatus());
    }
}

bool GoMarkovOperator::errorDetect()
{
    bool flag = false;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        if (this->input()->signal()->at(i) == 0)
        {
            flag = true;
            this->_error = QObject::tr("Error: Operator ") + GoMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 does not have input at %2.").arg(this->id()).arg(i + 1);
        }
    }
    for (int i = 0; i < this->subInput()->number(); ++i)
    {
        if (this->subInput()->signal()->at(i) == 0)
        {
            flag = true;
            this->_error = QObject::tr("Error: Operator ") + GoMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 does not have sub input at %2.").arg(this->id()).arg(i + 1);
        }
    }
    if (this->totalFrequencyBreakdown() > 1.0)
    {
        flag = true;
        this->_error = QObject::tr("Error: ") + GoMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 The total frequency of breakdown is greater than 1.").arg(this->id());
    }
    return flag;
}

bool GoMarkovOperator::isGlobalFeedback() const
{
    return this->_isGlobalFeedback;
}

void GoMarkovOperator::setIsGlobalFeedback(const bool value)
{
    this->_isGlobalFeedback = value;
}

QString GoMarkovOperator::error() const
{
    return this->_error;
}

DoubleVector GoMarkovOperator::totalFrequencyBreakdown() const
{
    DoubleVector total = this->markovStatus1()->frequencyBreakdown();
    if (this->breakdownNum() > 1)
    {
        total += this->markovStatus2()->frequencyBreakdown();
    }
    if (this->breakdownNum() > 2)
    {
        total += this->markovStatus3()->frequencyBreakdown();
    }
    if (this->breakdownNum() > 3)
    {
        total += this->markovStatus4()->frequencyBreakdown();
    }
    return total;
}

void GoMarkovOperator::initCalculation(double interval)
{
    if (this->breakdownNum() == 2)
    {
        DoubleVector lambda1 = this->markovStatus1()->frequencyBreakdown();
        DoubleVector lambda2 = this->markovStatus2()->frequencyBreakdown();
        DoubleVector mu1 = this->markovStatus1()->frequencyRepair();
        DoubleVector mu2 = this->markovStatus2()->frequencyRepair();
        this->_rkBreakdown2->setX(0.0);
        this->_rkBreakdown2->setY(0, 1.0);
        this->_rkBreakdown2->setLambda(lambda1.getValue(0), lambda2.getValue(0));
        this->_rkBreakdown2->setMu(mu1.getValue(0), mu2.getValue(0));
        for (int i = 1; i < 3; ++i)
        {
            this->_rkBreakdown2->setY(i, 0.0);
        }
        this->_rkBreakdown2->setH(interval);
    }
    else if (this->breakdownNum() == 3)
    {
        DoubleVector lambda1 = this->markovStatus1()->frequencyBreakdown();
        DoubleVector lambda2 = this->markovStatus2()->frequencyBreakdown();
        DoubleVector lambda3 = this->markovStatus3()->frequencyBreakdown();
        DoubleVector mu1 = this->markovStatus1()->frequencyRepair();
        DoubleVector mu2 = this->markovStatus2()->frequencyRepair();
        DoubleVector mu3 = this->markovStatus3()->frequencyRepair();
        this->_rkBreakdown3->setX(0.0);
        this->_rkBreakdown3->setY(0, 1.0);
        this->_rkBreakdown3->setLambda(lambda1.getValue(0), lambda2.getValue(0), lambda3.getValue(0));
        this->_rkBreakdown3->setMu(mu1.getValue(0), mu2.getValue(0), mu3.getValue(0));
        for (int i = 1; i < 4; ++i)
        {
            this->_rkBreakdown3->setY(i, 0.0);
        }
        this->_rkBreakdown3->setH(interval);
    }
    else if (this->breakdownNum() == 4)
    {
        DoubleVector lambda1 = this->markovStatus1()->frequencyBreakdown();
        DoubleVector lambda2 = this->markovStatus2()->frequencyBreakdown();
        DoubleVector lambda3 = this->markovStatus3()->frequencyBreakdown();
        DoubleVector lambda4 = this->markovStatus4()->frequencyBreakdown();
        DoubleVector mu1 = this->markovStatus1()->frequencyRepair();
        DoubleVector mu2 = this->markovStatus2()->frequencyRepair();
        DoubleVector mu3 = this->markovStatus3()->frequencyRepair();
        DoubleVector mu4 = this->markovStatus4()->frequencyRepair();
        this->_rkBreakdown4->setLambda(lambda1.getValue(0), lambda2.getValue(0), lambda3.getValue(0), lambda4.getValue(0));
        this->_rkBreakdown4->setMu(mu1.getValue(0), mu2.getValue(0), mu3.getValue(0), mu4.getValue(0));
        this->_rkBreakdown4->setX(0.0);
        this->_rkBreakdown4->setY(0, 1.0);
        for (int i = 1; i < 5; ++i)
        {
            this->_rkBreakdown4->setY(i, 0.0);
        }
        this->_rkBreakdown4->setH(interval);
    }
}

void GoMarkovOperator::prepareNextCalculation(int count, double time)
{
    Q_UNUSED(count);
    Q_UNUSED(time);
    if (this->breakdownNum() == 2)
    {
        this->_rkBreakdown2->nextStep();
    }
    if (this->breakdownNum() == 3)
    {
        this->_rkBreakdown3->nextStep();
    }
    else if (this->breakdownNum() == 4)
    {
        this->_rkBreakdown4->nextStep();
    }
}

void GoMarkovOperator::finishCalculation()
{
}

void GoMarkovOperator::initInfinityMarkovStatus()
{
    this->initMarkovStatus(1e10);
    if (this->breakdownNum() == 2)
    {
        this->_rkBreakdown2->calculateInfinity();
    }
    else if (this->breakdownNum() == 3)
    {
        this->_rkBreakdown3->calculateInfinity();
    }
    else if (this->breakdownNum() == 4)
    {
        this->_rkBreakdown4->calculateInfinity();
    }
}

RungeKuttaBreakdown2* GoMarkovOperator::rkBreakdown2() const
{
    return this->_rkBreakdown2;
}

RungeKuttaBreakdown3* GoMarkovOperator::rkBreakdown3() const
{
    return this->_rkBreakdown3;
}

RungeKuttaBreakdown4* GoMarkovOperator::rkBreakdown4() const
{
    return this->_rkBreakdown4;
}

GoMarkovOperator* GoMarkovOperator::copy()
{
    GoMarkovOperator *op = GoMarkovOperatorFactory::produce(this->TypedItem::type());
    op->setId(this->id());
    op->setRealID(this->realID());
    op->setType(this->TypedItem::type());
    op->input()->setNumber(this->input()->number());
    op->subInput()->setNumber(this->subInput()->number());
    op->output()->setNumber(this->output()->number());
    op->setName(this->name());

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

void GoMarkovOperator::save(QDomDocument &document, QDomElement &root)
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
}

bool GoMarkovOperator::tryOpen(QDomElement &root)
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
    return true;
}

void GoMarkovOperator::paintParameter(QPainter *painter)
{
    if (!GoMarkovOperatorFactory::isLogical(this->TypedItem::type()))
    {
        this->paintMarkovParameter(painter);
    }
}

void GoMarkovOperator::paintMarkovParameter(QPainter *painter)
{
    int y = 40;
    if (this->breakdownNum() > 0)
    {
        painter->drawText(-50, y, QObject::tr("Lambda 1: %1").arg(this->_markovStatus1->frequencyBreakdown().getValue(0)));
        painter->drawText(-50, y + 20, QObject::tr("    Mu 1: %1").arg(this->_markovStatus1->frequencyRepair().getValue(0)));
    }
    y += 40;
    if (this->breakdownNum() > 1)
    {
        painter->drawText(-50, y, QObject::tr("Lambda 2: %1").arg(this->_markovStatus2->frequencyBreakdown().getValue(0)));
        painter->drawText(-50, y + 20, QObject::tr("    Mu 2: %1").arg(this->_markovStatus2->frequencyRepair().getValue(0)));
    }
    y += 40;
    if (this->breakdownNum() > 2)
    {
        painter->drawText(-50, y, QObject::tr("Lambda 3: %1").arg(this->_markovStatus3->frequencyBreakdown().getValue(0)));
        painter->drawText(-50, y + 20, QObject::tr("    Mu 3: %1").arg(this->_markovStatus3->frequencyRepair().getValue(0)));
    }
    y += 40;
    if (this->breakdownNum() > 3)
    {
        painter->drawText(-50, y, QObject::tr("Lambda 4: %1").arg(this->_markovStatus4->frequencyBreakdown().getValue(0)));
        painter->drawText(-50, y + 20, QObject::tr("    Mu 4: %1").arg(this->_markovStatus4->frequencyRepair().getValue(0)));
    }
}
