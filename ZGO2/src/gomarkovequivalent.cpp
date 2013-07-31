#include "gomarkovequivalent.h"
#include "gomarkovoperator.h"
#include "goinput.h"

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
    this->_operators->clear();
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

void GOMarkovEquivalent::setI(int value)
{
    if (value < 0)
    {
        value = 0;
    }
    else
    {
        if (this->_operators->size() > 0)
        {
            if (this->_operators->at(this->_operators->size() - 1)->input()->number() > 1)
            {
                if (value > this->_operators->size() - 1)
                {
                    value = this->_operators->size() - 1;
                }
            }
            else
            {
                if (value > this->_operators->size())
                {
                    value = this->_operators->size();
                }
            }
        }
    }
    this->_I = value;
}

void GOMarkovEquivalent::setL(int value)
{
    if (value < 0)
    {
        value = 0;
    }
    else
    {
        if (this->_operators->size() > 0)
        {
            if (this->_operators->at(this->_operators->size() - 1)->input()->number() > 1)
            {
                if (value > this->_operators->size() - 1)
                {
                    value = this->_operators->size() - 1;
                }
            }
            else
            {
                if (value > this->_operators->size())
                {
                    value = this->_operators->size();
                }
            }
        }
    }
    this->_L = value;
}

void GOMarkovEquivalent::setJ(int value)
{
    if (value < 0)
    {
        value = 0;
    }
    else
    {
        if (this->_operators->size() > 0)
        {
            if (this->_operators->at(this->_operators->size() - 1)->input()->number() > 1)
            {
                if (value > this->_operators->size() - 1)
                {
                    value = this->_operators->size() - 1;
                }
            }
            else
            {
                if (value > this->_operators->size())
                {
                    value = this->_operators->size();
                }
            }
        }
    }
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
