#include "gooutput.h"
#include "gosignal.h"

GOOutput::GOOutput()
{
    this->_signal = new QVector<QVector<GOSignal*>*>();
}

GOOutput::~GOOutput()
{
    this->clear();
    delete this->_signal;
}

int GOOutput::number() const
{
    return this->_signal->size();
}

void GOOutput::setNumber(int num)
{
    this->clear();
    for (int i = 0; i < num; ++i)
    {
        this->_signal->push_back(new QVector<GOSignal*>());
    }
}

QVector<QVector<GOSignal*>*>* GOOutput::signal() const
{
    return this->_signal;
}

int GOOutput::getSignalIndex(GOSignal* signal) const
{
    for (int i = 0; i < this->_signal->size(); ++i)
    {
        for (int j = 0; j < this->_signal->at(i)->size(); ++j)
        {
            if (this->_signal->at(i)->at(j) == signal)
            {
                return i;
            }
        }
    }
    return -1;
}

void GOOutput::clear()
{
    for (int i = 0; i < this->_signal->size(); ++i)
    {
        for (int j = 0; j < this->signal()->at(i)->size(); ++j)
        {
            delete this->_signal->at(i)->at(j);
        }
        this->_signal->at(i)->clear();
    }
    this->_signal->clear();
}
