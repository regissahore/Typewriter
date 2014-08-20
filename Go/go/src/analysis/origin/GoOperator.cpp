#include "GoOperator.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoAccumulative.h"
#include "GoParameter.h"

GoOperator::GoOperator()
{
    this->setRealID(0);
    this->setName("");
    this->_input = new GoInput();
    this->_subInput = new GoInput();
    this->_output = new GoOutput();
    this->_status = new GoStatus();
    this->_accumulatives = new QVector<GoAccumulative*>();
    this->_parameter = new GoParameter();
}

int GoOperator::realID() const
{
    return this->_realID;
}

void GoOperator::setRealID(const int value)
{
    this->_realID = value;
}

GoOperator::~GoOperator()
{
    delete this->_input;
    delete this->_subInput;
    delete this->_output;
    delete this->_status;
    for (int i = 0; i < this->_accumulatives->size(); ++i)
    {
        delete this->_accumulatives->at(i);
    }
    this->_accumulatives->clear();
    delete this->_accumulatives;
    delete this->_parameter;
}

GoInput *GoOperator::input() const
{
    return this->_input;
}

GoInput *GoOperator::subInput() const
{
    return this->_subInput;
}

GoOutput* GoOperator::output() const
{
    return this->_output;
}

GoStatus* GoOperator::status() const
{
    return this->_status;
}

QVector<GoAccumulative *>* GoOperator::accmulatives() const
{
    return this->_accumulatives;
}

GoParameter* GoOperator::parameter() const
{
    return this->_parameter;
}

QString GoOperator::name() const
{
    return this->_name;
}

void GoOperator::setName(const QString name)
{
    this->_name = name;
}

void GoOperator::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("real", this->realID());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    element.setAttribute("name", this->name());
    root.appendChild(element);
    this->status()->save(document, element);
    this->parameter()->save(document, element);
}

bool GoOperator::tryOpen(QDomElement &root)
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
    this->setName(root.attribute("name", ""));
    QDomElement element = root.firstChildElement();
    if (!this->status()->tryOpen(element))
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
