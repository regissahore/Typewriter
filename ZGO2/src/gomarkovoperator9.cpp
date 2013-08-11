#include <qmath.h>
#include "gomarkovoperator9.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator9::GOMarkovOperator9() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->_feedbackStatus = new GOMarkovStatus();
}

GOMarkovOperator9::~GOMarkovOperator9()
{
    this->GOMarkovOperator::~GOMarkovOperator();
    delete this->_feedbackStatus;
}

GOMarkovOperator* GOMarkovOperator9::copy()
{
    GOMarkovOperator9 *op = (GOMarkovOperator9*)this->GOMarkovOperator::copy();
    op->markovFeedbackStatus()->setProbabilityNormal(this->markovFeedbackStatus()->probabilityNormal());
    op->markovFeedbackStatus()->setFrequencyBreakdown(this->markovFeedbackStatus()->frequencyBreakdown());
    op->markovFeedbackStatus()->setFrequencyRepair(this->markovFeedbackStatus()->frequencyRepair());
    return op;
}

GOMarkovStatus* GOMarkovOperator9::markovFeedbackStatus() const
{
    return this->_feedbackStatus;
}

void GOMarkovOperator9::save(QDomDocument &document, QDomElement &root)
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
    this->markovFeedbackStatus()->save(document, element);
}

bool GOMarkovOperator9::tryOpen(QDomElement &root)
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
    element = element.nextSiblingElement();
    if (!this->markovFeedbackStatus()->tryOpen(element))
    {
        return false;
    }
    return true;
}
