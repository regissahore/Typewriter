#include <QObject>
#include <qmath.h>
#include "gomarkovoperator22.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"
#include "messager.h"
#include "messagefactory.h"
#include "gomarkovoperatorfactory.h"

GOMarkovOperator22::GOMarkovOperator22() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->_lambda2 = new QVector<double>();
    this->_mu2 = new QVector<double>();
}

GOMarkovOperator22::~GOMarkovOperator22()
{
    this->GOMarkovOperator::~GOMarkovOperator();
    this->_lambda2->clear();
    this->_mu2->clear();
    delete this->_lambda2;
    delete this->_mu2;
}

QVector<double>* GOMarkovOperator22::lambda2() const
{
    return this->_lambda2;
}

QVector<double>* GOMarkovOperator22::mu2() const
{
    return this->_mu2;
}

bool GOMarkovOperator22::errorDetect(Messager *messager)
{
    if (this->GOMarkovOperator::errorDetect(messager))
    {
        return true;
    }
    GOMarkovOperator *op = this->getPrevSubOperator();
    if (!GOMarkovOperatorFactory::isVectorOutput(op->TypedItem::type()))
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_ERROR);
        message->paramString = QObject::tr("Error: Operator ") + GOMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 The sub-input should be a vector.").arg(this->id());
        messager->sendMessage(message);
        return true;
    }
    if (this->output()->number() != op->markovOutputStatus()->size())
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_ERROR);
        message->paramString = QObject::tr("Error: Operator ") + GOMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 The number of output should matches the length of the input vector.").arg(this->id());
        messager->sendMessage(message);
        return true;
    }
    return false;
}

GOMarkovOperator* GOMarkovOperator22::copy()
{
    GOMarkovOperator22 *op = (GOMarkovOperator22*)this->GOMarkovOperator::copy();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        op->lambda2()->push_back(this->lambda2()->at(i));
        op->mu2()->push_back(this->mu2()->at(i));
    }
    return op;
}

void GOMarkovOperator22::save(QDomDocument &document, QDomElement &root)
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

bool GOMarkovOperator22::tryOpen(QDomElement &root)
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
        this->lambda2()->push_back(node.attribute("lambda").toDouble());
        this->mu2()->push_back(node.attribute("mu").toDouble());
        node = node.nextSiblingElement();
    }
    return true;
}
