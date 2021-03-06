#include <qmath.h>
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"
#include "RungeKuttaMarkov18.h"
#include "GoMarkovOperator18.h"

GoMarkovOperator18::GoMarkovOperator18() : GoMarkovOperator()
{
    this->input()->setNumber(2);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator18::~GoMarkovOperator18()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator18::calcQualitativeProbability()
{
    DoubleVector IS1 = this->getPrevQualitativeStatus(0);
    DoubleVector IS2 = this->getPrevQualitativeStatus(1);
    DoubleVector IR = 1.0 - (1.0 - IS1) * (1.0 - IS2);
    this->_qualitativeOutput[0] = IR;
}

double GoMarkovOperator18::lambdaB1() const
{
    return this->_lambdaB1;
}

void GoMarkovOperator18::setLambdaB1(double value)
{
    this->_lambdaB1 = value;
}

void GoMarkovOperator18::calcOutputMarkovStatus(double time)
{
    GoMarkovStatus *status;
    status = this->getPrevMarkovStatus(0);
    DoubleVector PS1 = status->probabilityNormal();
    DoubleVector lambda1 = status->frequencyBreakdown();
    DoubleVector mu1 = status->frequencyRepair();
    status = this->getPrevMarkovStatus(1);
    DoubleVector lambda2 = status->frequencyBreakdown();
    DoubleVector mu2 = status->frequencyRepair();
    this->_rk18.setLambda(lambda1.getValue(0), lambda2.getValue(0), this->_lambdaB1);
    this->_rk18.setMu(mu1.getValue(0), mu2.getValue(0));
    this->_rk18.setH(time / 10000);
    this->_rk18.setX(0.0);
    this->_rk18.setY(0, 1.0);
    for (int i = 1; i < 4; ++i)
    {
        this->_rk18.setY(i, 0.0);
    }
    for (int i = 0; i < 10000; ++i)
    {
        this->_rk18.nextStep();
    }
    DoubleVector PR = PS1 + this->_rk18.getY(0);
    DoubleVector lambdaR = (lambda1 * (PS1 - this->_rk18.getY(0)) + lambda2 * this->_rk18.getY(0)) / (PS1 + this->_rk18.getY(0));
    DoubleVector muR = mu1 + mu2;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GoMarkovOperator18::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    GoMarkovStatus *status;
    status = this->getPrevMarkovStatus(0);
    DoubleVector PS1 = input[0];
    DoubleVector lambda1 = status->frequencyBreakdown();
    DoubleVector mu1 = status->frequencyRepair();
    status = this->getPrevMarkovStatus(1);
    DoubleVector lambda2 = status->frequencyBreakdown();
    DoubleVector mu2 = status->frequencyRepair();
    this->_rk18.setLambda(lambda1.getValue(0), lambda2.getValue(0), this->_lambdaB1);
    this->_rk18.setMu(mu1.getValue(0), mu2.getValue(0));
    this->_rk18.setH(time / 10000);
    this->_rk18.setX(0.0);
    this->_rk18.setY(0, 1.0);
    for (int i = 1; i < 4; ++i)
    {
        this->_rk18.setY(i, 0.0);
    }
    for (int i = 0; i < 10000; ++i)
    {
        this->_rk18.nextStep();
    }
    DoubleVector PR = PS1 + this->_rk18.getY(0);
    return PR;
}

GoMarkovOperator* GoMarkovOperator18::copy()
{
    GoMarkovOperator18 *op = (GoMarkovOperator18*)this->GoMarkovOperator::copy();
    op->setLambdaB1(this->lambdaB1());
    return op;
}

void GoMarkovOperator18::save(QDomDocument &document, QDomElement &root)
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
    element.setAttribute("lambdab1", this->lambdaB1());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->markovStatus3()->save(document, element);
    this->markovStatus4()->save(document, element);
}

bool GoMarkovOperator18::tryOpen(QDomElement &root)
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
    this->setLambdaB1(root.attribute("lambdab1").toDouble());
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
