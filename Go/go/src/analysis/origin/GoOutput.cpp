#include "GoOutput.h"
#include "GoSignal.h"

GoOutput::GoOutput()
{
    this->_signal = new QVector<QVector<GoSignal*>*>();
}

GoOutput::~GoOutput()
{
    this->clear();
    delete this->_signal;
}

int GoOutput::number() const
{
    return this->_signal->size();
}

void GoOutput::setNumber(int num)
{
    this->clear();
    for (int i = 0; i < num; ++i)
    {
        this->_signal->push_back(new QVector<GoSignal*>());
    }
}

QVector<QVector<GoSignal*>*>* GoOutput::signal() const
{
    return this->_signal;
}

int GoOutput::getSignalIndex(GoSignal* signal) const
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

void GoOutput::addSignal(int index, GoSignal *signal)
{
    for (int i = 0; i < this->_signal->at(index)->size(); ++i)
    {
        if (this->_signal->at(index)->at(i) == signal)
        {
            return;
        }
    }
    this->_signal->at(index)->push_back(signal);
}

void GoOutput::clear()
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
