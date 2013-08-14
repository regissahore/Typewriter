#include <qmath.h>
#include "gomarkovoperator18.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"
#include "rungekuttamarkov18.h"

GOMarkovOperator18::GOMarkovOperator18() : GOMarkovOperator()
{
    this->input()->setNumber(2);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->_rungeKutta = new RungeKuttaMarkov18();
    this->_rungeKutta->setLambdaB1(0.0);
}

GOMarkovOperator18::~GOMarkovOperator18()
{
    this->GOMarkovOperator::~GOMarkovOperator();
    delete this->_rungeKutta;
}

double GOMarkovOperator18::lambdaB1() const
{
    return this->_rungeKutta->lambdaB1();
}

void GOMarkovOperator18::setLambdaB1(double value)
{
    this->_rungeKutta->setLambdaB1(value);
}

void GOMarkovOperator18::calcOutputMarkovStatus(double time)
{
    GOMarkovStatus *status;
    status = this->getPrevMarkovStatus(0);
    double PS1 = status->probabilityNormal();
    double lambda1 = status->frequencyBreakdown();
    double mu1 = status->frequencyRepair();
    status = this->getPrevMarkovStatus(1);
    double lambda2 = status->frequencyBreakdown();
    double mu2 = status->frequencyRepair();
    this->_rungeKutta->calcNormalProbability(time, lambda1, lambda2, mu1, mu2);
    double PR = PS1 + this->_rungeKutta->rk1();
    double lambdaR = (lambda1 * (PS1 - this->_rungeKutta->rk0()) + lambda2 * this->_rungeKutta->rk1()) / (PS1 + this->_rungeKutta->rk1());
    double muR = mu1 + mu2;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator18::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    GOMarkovStatus *status;
    status = this->getPrevMarkovStatus(0);
    double PS1 = input[0];
    double lambda1 = status->frequencyBreakdown();
    double mu1 = status->frequencyRepair();
    status = this->getPrevMarkovStatus(1);
    double lambda2 = status->frequencyBreakdown();
    double mu2 = status->frequencyRepair();
    this->_rungeKutta->calcNormalProbability(time, lambda1, lambda2, mu1, mu2);
    double PR = PS1 + this->_rungeKutta->rk1();
    return PR;
}

GOMarkovOperator* GOMarkovOperator18::copy()
{
    GOMarkovOperator18 *op = (GOMarkovOperator18*)this->GOMarkovOperator::copy();
    op->setLambdaB1(this->lambdaB1());
    return op;
}

void GOMarkovOperator18::save(QDomDocument &document, QDomElement &root)
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
    element.setAttribute("lambdab1", this->_rungeKutta->lambdaB1());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->markovStatus3()->save(document, element);
    this->markovStatus4()->save(document, element);
}

bool GOMarkovOperator18::tryOpen(QDomElement &root)
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
    this->_rungeKutta->setLambdaB1(root.attribute("lambdab1").toDouble());
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
