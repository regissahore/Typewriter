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
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->saveRelation(document, element);
    this->parameter()->save(document, element);
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

bool GOMarkovOperator13::tryOpen(QDomElement &root)
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
    if (!this->tryOpenRelation(element))
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
            (*this->_relation)[i][j] = dataElement.attribute("value").toDouble();
            dataElement = dataElement.nextSiblingElement();
        }
        rowElement = rowElement.nextSiblingElement();
    }
    return true;
}

GOMarkovOperator* GOMarkovOperator13::copy()
{
    GOMarkovOperator13 *op = new GOMarkovOperator13();
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
