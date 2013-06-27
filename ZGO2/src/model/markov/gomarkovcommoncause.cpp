#include "gomarkovcommoncause.h"
#include "gomarkovoperator.h"

GOMarkovCommonCause::GOMarkovCommonCause() : DomItem()
{
    this->_commonCause = 0.0;
    this->_idList = new QVector<int>();
    this->_operators = new QVector<GOMarkovOperator*>();
}

GOMarkovCommonCause::~GOMarkovCommonCause()
{
    this->_idList->clear();
    delete this->_idList;
    this->_operators->clear();
    delete this->_operators;
}

double GOMarkovCommonCause::commonCause() const
{
    return this->_commonCause;
}

void GOMarkovCommonCause::setCommonCause(double value)
{
    this->_commonCause = value;
}

void GOMarkovCommonCause::save(QDomDocument &document, QDomElement &root)
{
    QDomElement commonRoot = document.createElement("commoncause");
    commonRoot.setAttribute("value", this->commonCause());
    for (int i = 0; i < this->operators()->size(); ++i)
    {
        QDomElement element = document.createElement("operator");
        element.setAttribute("id", this->operators()->at(i)->id());
        commonRoot.appendChild(element);
    }
    root.appendChild(commonRoot);
}

bool GOMarkovCommonCause::tryOpen(QDomElement &root)
{
    if (root.tagName() != "commoncause")
    {
        return false;
    }
    this->setCommonCause(root.attribute("value").toDouble());
    this->_idList->clear();
    for (QDomElement element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        this->_idList->push_back(element.attribute("id").toInt());
    }
    return true;
}

QVector<GOMarkovOperator*>* GOMarkovCommonCause::operators() const
{
    return this->_operators;
}

QVector<int>* GOMarkovCommonCause::idList() const
{
    return this->_idList;
}
