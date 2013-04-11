#include "gomarkovequivalent.h"
#include "gomarkovoperator.h"

GOMarkovEquivalent::GOMarkovEquivalent() : IdentifiedItem()
{
    this->_operators = new QVector<GOMarkovOperator*>();
    this->_equivalents = new QVector<GOMarkovEquivalent*>();
    this->_idList = new QVector<int>();
    this->_I = 0;
    this->_L = 0;
    this->_J = 0;
}

GOMarkovEquivalent::~GOMarkovEquivalent()
{
    for (int i = 0; i < this->_operators->size(); ++i)
    {
        delete this->_operators->at(i);
    }
    delete this->_operators;
    for (int i = 0; i < this->_equivalents->size(); ++i)
    {
        delete this->_equivalents->at(i);
    }
    delete this->_equivalents;
    this->_idList->clear();
    delete this->_idList;
}

QVector<GOMarkovOperator*>* GOMarkovEquivalent::operators() const
{
    return this->_operators;
}

QVector<GOMarkovEquivalent*>* GOMarkovEquivalent::equivalents() const
{
    return this->_equivalents;
}

int GOMarkovEquivalent::I() const
{
    return this->_I;
}

int GOMarkovEquivalent::L() const
{
    return this->_L;
}

int GOMarkovEquivalent::J() const
{
    return this->_J;
}

void GOMarkovEquivalent::setI(const int value)
{
    this->_I = value;
}

void GOMarkovEquivalent::setL(const int value)
{
    this->_L = value;
}

void GOMarkovEquivalent::setJ(const int value)
{
    this->_J = value;
}

QVector<int>* GOMarkovEquivalent::idList() const
{
    return this->_idList;
}

void GOMarkovEquivalent::save(QDomDocument &document, QDomElement &root)
{
    Q_UNUSED(document);
    Q_UNUSED(root);
}

bool GOMarkovEquivalent::tryOpen(QDomElement &root)
{
    Q_UNUSED(root);
    return true;
}
