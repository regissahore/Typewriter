#include "gomarkovoperator9a.h"
#include "gomarkovstatus.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "goparameter.h"

GOMarkovOperator9A::GOMarkovOperator9A() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->_feedbackStatus = new GOMarkovStatus();
}

GOMarkovOperator9A::~GOMarkovOperator9A()
{
    this->GOMarkovOperator::~GOMarkovOperator();
    delete this->_feedbackStatus;
}

GOMarkovStatus* GOMarkovOperator9A::markovFeedbackStatus() const
{
    return this->_feedbackStatus;
}

GOMarkovOperator* GOMarkovOperator9A::copy()
{
    GOMarkovOperator9A *op = (GOMarkovOperator9A*)this->GOMarkovOperator::copy();
    op->markovFeedbackStatus()->setProbabilityNormal(this->markovFeedbackStatus()->probabilityNormal());
    op->markovFeedbackStatus()->setFrequencyBreakdown(this->markovFeedbackStatus()->frequencyBreakdown());
    op->markovFeedbackStatus()->setFrequencyRepair(this->markovFeedbackStatus()->frequencyRepair());
    return op;
}

void GOMarkovOperator9A::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    element.setAttribute("dual", this->breakdownNum());
    element.setAttribute("breakdown", this->isBreakdownCorrelate());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->markovFeedbackStatus()->save(document, element);
}

bool GOMarkovOperator9A::tryOpen(QDomElement &root)
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
    if (!this->markovFeedbackStatus()->tryOpen(element))
    {
        return false;
    }
    return true;
}
