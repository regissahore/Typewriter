#include "gooperator.h"
#include "goiomodel.h"
#include "gostatus.h"

/**
 * 构造函数。
 */
GOOperator::GOOperator()
{
    this->_input = new GOIOModel();
    this->_subInput = new GOIOModel();
    this->_output = new GOIOModel();
    this->_status = new GOStatus();
}

/**
 * 返回主输入信号流。
 * @return 主输入信号流。
 */
GOIOModel *GOOperator::input() const
{
    return this->_input;
}

/**
 * 返回次输入信号流。
 * @return 次输入信号流。
 */
GOIOModel *GOOperator::subInput() const
{
    return this->_subInput;
}

/**
 * 返回输出信号流。
 * @return 输出信号流。
 */
GOIOModel *GOOperator::output() const
{
    return this->_output;
}

GOStatus* GOOperator::status() const
{
    return this->_status;
}

void GOOperator::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    root.appendChild(element);
    this->input()->save(document, element);
    this->subInput()->save(document, element);
    this->output()->save(document, element);
    this->status()->save(document, element);
}

bool GOOperator::tryOpen(QDomElement &root)
{
    if (root.tagName() != "model")
    {
        return false;
    }
    this->setType(root.attribute("type").toInt());
    this->setId(root.attribute("id").toInt());
    QDomElement element = root.firstChildElement();
    if (!this->input()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->subInput()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->output()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->status()->tryOpen(element))
    {
        return false;
    }
    return true;
}
