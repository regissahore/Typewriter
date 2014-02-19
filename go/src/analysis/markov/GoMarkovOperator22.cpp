#include <QObject>
#include <qmath.h>
#include "GoMarkovOperator22.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"
#include "Messager.h"
#include "MessageFactory.h"
#include "GoMarkovOperatorFactory.h"

GoMarkovOperator22::GoMarkovOperator22() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->_lambda2 = new QVector<double>();
    this->_mu2 = new QVector<double>();
}

GoMarkovOperator22::~GoMarkovOperator22()
{
    this->GoMarkovOperator::~GoMarkovOperator();
    this->_lambda2->clear();
    this->_mu2->clear();
    delete this->_lambda2;
    delete this->_mu2;
}

QVector<double>* GoMarkovOperator22::lambda2() const
{
    return this->_lambda2;
}

QVector<double>* GoMarkovOperator22::mu2() const
{
    return this->_mu2;
}

GoMarkovOperator* GoMarkovOperator22::copy()
{
    GoMarkovOperator22 *op = (GoMarkovOperator22*)this->GoMarkovOperator::copy();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        op->lambda2()->push_back(this->lambda2()->at(i));
        op->mu2()->push_back(this->mu2()->at(i));
    }
    return op;
}

void GoMarkovOperator22::save(QDomDocument &document, QDomElement &root)
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
    for (int i = 0; i < this->output()->number(); ++i)
    {
        QDomElement node = document.createElement("node");
        node.setAttribute("lambda", this->lambda2()->at(i));
        node.setAttribute("mu", this->mu2()->at(i));
        subElement.appendChild(node);
    }
    element.appendChild(subElement);
}

bool GoMarkovOperator22::tryOpen(QDomElement &root)
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
    for (int i = 0; i < this->output()->number(); ++i)
    {
        this->lambda2()->push_back(node.attribute("lambda", "0.0").toDouble());
        this->mu2()->push_back(node.attribute("mu", "1.0").toDouble());
        node = node.nextSiblingElement();
    }
    return true;
}
