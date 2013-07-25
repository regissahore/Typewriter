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
    GOMarkovOperator9A *op = new GOMarkovOperator9A();
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
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovFeedbackStatus()->save(document, element);
    this->parameter()->save(document, element);
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
    if (!this->markovFeedbackStatus()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->parameter()->tryOpen(element))
    {
        return false;
    }
    return true;
}
