#include "gomarkovoperator13.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator13::GOMarkovOperator13() : GOMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(3);
    this->_relation = new QVector<QVector<int> >();
}

GOMarkovOperator13::~GOMarkovOperator13()
{
    this->GOMarkovOperator::~GOMarkovOperator();
    for (int i = 0; i < this->_relation->size(); ++i)
    {
        (*this->_relation)[i].clear();
    }
    this->_relation->clear();
    delete this->_relation;
}

void GOMarkovOperator13::initRelation()
{
    this->_relation->clear();
    for (int i = 0; i < this->input()->number(); ++i)
    {
        this->_relation->push_back(QVector<int>());
        for (int j = 0; j < this->output()->number(); ++j)
        {
            (*this->_relation)[i].push_back(0);
        }
    }
}

QVector<QVector<int> > *GOMarkovOperator13::relation()
{
    return this->_relation;
}

void GOMarkovOperator13::save(QDomDocument &document, QDomElement &root)
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
    this->saveRelation(document, element);
}

bool GOMarkovOperator13::tryOpen(QDomElement &root)
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
    if (!this->tryOpenRelation(element))
    {
        return false;
    }
    return true;
}

void GOMarkovOperator13::saveRelation(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("relation");
    for (int i = 0; i < this->_relation->size(); ++i)
    {
        QDomElement rowElement = document.createElement("row");
        for (int j = 0; j < this->_relation->at(i).size(); ++j)
        {
            QDomElement dataElement = document.createElement("data");
            dataElement.setAttribute("value", this->_relation->at(i).at(j));
            rowElement.appendChild(dataElement);
        }
        element.appendChild(rowElement);
    }
    root.appendChild(element);
}

bool GOMarkovOperator13::tryOpenRelation(QDomElement &root)
{
    if (root.tagName() != "relation")
    {
        return false;
    }
    this->initRelation();
    QDomElement rowElement = root.firstChildElement();
    for (int i = 0; i < this->_relation->size(); ++i)
    {
        QDomElement dataElement = rowElement.firstChildElement();
        for (int j = 0; j < this->_relation->at(i).size(); ++j)
        {
            (*this->_relation)[i][j] = dataElement.attribute("value").toInt();
            dataElement = dataElement.nextSiblingElement();
        }
        rowElement = rowElement.nextSiblingElement();
    }
    return true;
}

GOMarkovOperator* GOMarkovOperator13::copy()
{
    GOMarkovOperator13 *op = (GOMarkovOperator13*)this->GOMarkovOperator::copy();
    op->initRelation();
    for (int i = 0; i < this->relation()->size(); ++i)
    {
        for (int j = 0; j < this->relation()->at(i).size(); ++j)
        {
            (*(op->relation()))[i][j] = op->relation()->at(i).at(j);
        }
    }
    return op;
}
