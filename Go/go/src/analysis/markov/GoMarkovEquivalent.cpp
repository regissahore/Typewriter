#include "GoMarkovEquivalent.h"
#include "GoMarkovOperator.h"
#include "GoInput.h"

GoMarkovEquivalent::GoMarkovEquivalent() : IdentifiedItem()
{
    this->_operators = new QVector<GoMarkovOperator*>();
    this->_equivalents = new QVector<GoMarkovEquivalent*>();
    this->_idList = new QVector<int>();
    this->_I = 0;
    this->_L = 0;
    this->_J = 0;
}

GoMarkovEquivalent::~GoMarkovEquivalent()
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

QVector<GoMarkovOperator*>* GoMarkovEquivalent::operators() const
{
    return this->_operators;
}

QVector<GoMarkovEquivalent*>* GoMarkovEquivalent::equivalents() const
{
    return this->_equivalents;
}

int GoMarkovEquivalent::I() const
{
    return this->_I;
}

int GoMarkovEquivalent::L() const
{
    return this->_L;
}

int GoMarkovEquivalent::J() const
{
    return this->_J;
}

void GoMarkovEquivalent::setI(int value)
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

void GoMarkovEquivalent::setL(int value)
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

void GoMarkovEquivalent::setJ(int value)
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

QVector<int>* GoMarkovEquivalent::idList() const
{
    return this->_idList;
}

void GoMarkovEquivalent::save(QDomDocument &document, QDomElement &root)
{
    Q_UNUSED(document);
    Q_UNUSED(root);
}

bool GoMarkovEquivalent::tryOpen(QDomElement &root)
{
    Q_UNUSED(root);
    return true;
}
