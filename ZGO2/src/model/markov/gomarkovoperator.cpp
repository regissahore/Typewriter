#include "gomarkovoperator.h"
#include "gomarkovstatus.h"
#include "goinput.h"
#include "gooutput.h"
#include "goparameter.h"

GOMarkovOperator::GOMarkovOperator()
{
    this->_input = new GOInput();
    this->_subInput = new GOInput();
    this->_output = new GOOutput();
    this->_status = new GOMarkovStatus();
    this->_outputStatus = new QVector<GOMarkovStatus*>();
    this->_parameter = new GOParameter();
}

GOMarkovOperator::~GOMarkovOperator()
{
    delete this->_input;
    delete this->_subInput;
    delete this->_output;
    delete this->_status;
    for (int i = 0; i < this->_outputStatus->size(); ++i)
    {
        delete this->_outputStatus->at(i);
    }
    delete this->_outputStatus;
    delete this->_parameter;
}

GOInput* GOMarkovOperator::input() const
{
    return this->_input;
}

GOInput* GOMarkovOperator::subInput() const
{
    return this->_subInput;
}

GOOutput* GOMarkovOperator::output() const
{
    return this->_output;
}

GOMarkovStatus* GOMarkovOperator::status() const
{
    return this->_status;
}

QVector<GOMarkovStatus*>* GOMarkovOperator::outputStatus() const
{
    return this->_outputStatus;
}

GOParameter *GOMarkovOperator::parameter() const
{
    return this->_parameter;
}

void GOMarkovOperator::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    root.appendChild(element);
    this->parameter()->save(document, element);
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
    QDomElement element = root.firstChildElement();
    if (!this->parameter()->tryOpen(element))
    {
        return false;
    }
    return true;
}
