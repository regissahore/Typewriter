#include <QObject>
#include <qmath.h>
#include "gomarkovoperator19.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"
#include "messager.h"
#include "messagefactory.h"
#include "gomarkovoperatorfactory.h"

GOMarkovOperator19::GOMarkovOperator19() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(2);
    this->_deltaNum = 1;
    this->_a = new QVector<int>();
    this->_delta = new QVector<double>();
    this->_a->push_back(1);
    this->_delta->push_back(0.0);
}

GOMarkovOperator19::~GOMarkovOperator19()
{
    this->GOMarkovOperator::~GOMarkovOperator();
    this->_a->clear();
    delete this->_a;
    this->_delta->clear();
    delete this->_delta;
}

QVector<int>* GOMarkovOperator19::a() const
{
    return this->_a;
}

QVector<double>* GOMarkovOperator19::delta() const
{
    return this->_delta;
}

int GOMarkovOperator19::deltaNum() const
{
    return this->_deltaNum;
}

void GOMarkovOperator19::setDeltaNum(int value)
{
    this->_deltaNum = value;
}

void GOMarkovOperator19::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GOMarkovOperator *prevOperator = this->getPrevOperator();
    QVector<double> PS;
    QVector<double> lambdaS;
    QVector<double> muS;
    int N = prevOperator->markovOutputStatus()->size();
    for (int i = 0; i < N; ++i)
    {
        GOMarkovStatus *status = prevOperator->markovOutputStatus()->at(i);
        PS.push_back(status->probabilityNormal());
        lambdaS.push_back(status->frequencyBreakdown());
        muS.push_back(status->frequencyRepair());
        if (this->a()->at(i) == 1)
        {
            PS[i] *= this->delta()->at(i);
        }
        else
        {
            PS[i] = (1 - PS[i]) * this->delta()->at(i);
        }
        lambdaS[i] *= this->delta()->at(i);
        muS[i] *= this->delta()->at(i);
    }
    double PC = this->markovStatus()->probabilityNormal();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double PR2 = 0.0;
    double lambdaR2 = 0.0;
    double muR2 = 0.0;
    for (int i = 1; i < N - 1; ++i)
    {
        PR2 += PS[i] * PC;
        lambdaR2 += (lambdaS[i] + lambdaC) * PS[i] * PC;
        muR2 += lambdaS[i] + lambdaC;
    }
    double QR2 = 1.0 - PR2;
    muR2 *= PR2 / QR2;
    double PR1 = PR2 + PS[0];
    double lambdaR1 = lambdaR2 + lambdaS[0] * PS[0];
    lambdaR2 /= PR2;
    lambdaR1 /= PR1;
    double muR1 = muR2 + muS[0];
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR1);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR1);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR1);
    this->markovOutputStatus()->at(1)->setProbabilityNormal(PR2);
    this->markovOutputStatus()->at(1)->setFrequencyBreakdown(lambdaR2);
    this->markovOutputStatus()->at(1)->setFrequencyRepair(muR2);
}

double GOMarkovOperator19::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    QVector<double> PS;
    int N = input.size();
    for (int i = 0; i < N; ++i)
    {
        PS.push_back(input[i]);
    }
    double PC = this->markovStatus()->probabilityNormal();
    double PR2 = 0.0;
    for (int i = 1; i < N - 1; ++i)
    {
        PR2 += PS[i] * PC;
    }
    double PR1 = PR2 + PS[0];
    if (index == 0)
    {
        return PR1;
    }
    return PR2;
}

bool GOMarkovOperator19::errorDetect(Messager *messager)
{
    if (this->GOMarkovOperator::errorDetect(messager))
    {
        return true;
    }
    GOMarkovOperator *op = this->getPrevOperator();
    if (!GOMarkovOperatorFactory::isVectorOutput(op->TypedItem::type()))
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_ERROR);
        message->paramString = QObject::tr("Error: Operator ") + GOMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 The input should be a vector.").arg(this->id());
        messager->sendMessage(message);
        return true;
    }
    return false;
}

GOMarkovOperator* GOMarkovOperator19::copy()
{
    GOMarkovOperator19 *op = (GOMarkovOperator19*)this->GOMarkovOperator::copy();
    op->setDeltaNum(this->deltaNum());
    for (int i = 0; i < this->deltaNum(); ++i)
    {
        op->a()->push_back(this->a()->at(i));
        op->delta()->push_back(this->delta()->at(i));
    }
    return op;
}

void GOMarkovOperator19::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    element.setAttribute("dual", this->breakdownNum());
    element.setAttribute("breakdown", this->isBreakdownCorrelate());
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
        node.setAttribute("a", this->a()->at(i));
        node.setAttribute("delta", this->delta()->at(i));
        subElement.appendChild(node);
    }
    element.appendChild(subElement);
}

bool GOMarkovOperator19::tryOpen(QDomElement &root)
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
    this->a()->clear();
    this->delta()->clear();
    for (int i = 0; i < this->deltaNum(); ++i)
    {
        this->a()->push_back(node.attribute("a").toInt());
        this->delta()->push_back(node.attribute("delta").toDouble());
        node = node.nextSiblingElement();
    }
    return true;
}
