#include "gooperator.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "goaccumulative.h"
#include "goparameter.h"

/**
 * 构造函数。
 */
GOOperator::GOOperator()
{
    this->_input = new GOInput();
    this->_subInput = new GOInput();
    this->_output = new GOOutput();
    this->_status = new GOStatus();
    this->_accumulatives = new QVector<GOAccumulative*>();
    this->_parameter = new GOParameter();
}

GOOperator::~GOOperator()
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

/**
 * 返回主输入信号流。
 * @return 主输入信号流。
 */
GOInput *GOOperator::input() const
{
    return this->_input;
}

/**
 * 返回次输入信号流。
 * @return 次输入信号流。
 */
GOInput *GOOperator::subInput() const
{
    return this->_subInput;
}

/**
 * 返回输出信号流。
 * @return 输出信号流。
 */
GOOutput* GOOperator::output() const
{
    return this->_output;
}

GOStatus* GOOperator::status() const
{
    return this->_status;
}

QVector<GOAccumulative *>* GOOperator::accmulatives() const
{
    return this->_accumulatives;
}

GOParameter* GOOperator::parameter() const
{
    return this->_parameter;
}

void GOOperator::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    root.appendChild(element);
    this->status()->save(document, element);
    this->parameter()->save(document, element);
}

bool GOOperator::tryOpen(QDomElement &root)
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
    if (!this->parameter()->tryOpen(element))
    {
        return false;
    }
    return true;
}
