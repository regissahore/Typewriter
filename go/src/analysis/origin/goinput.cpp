#include "GoInput.h"
#include "GoSignal.h"

GoInput::GoInput()
{
    this->_signal = new QVector<GoSignal*>();
}

GoInput::~GoInput()
{
    this->_signal->clear();
    delete this->_signal;
}

int GoInput::number() const
{
    return this->_signal->size();
}

void GoInput::setNumber(int num)
{
    if (this->number() < num)
    {
        num = num - this->number();
        while (num--)
        {
            this->add(nullptr);
        }
    }
    else if (this->number() > num)
    {
        num = this->number() - num;
        while (num--)
        {
            this->remove(this->number() - 1);
        }
    }
}

void GoInput::add(GoSignal *signal)
{
    this->_signal->push_back(signal);
}

void GoInput::set(int index, GoSignal *signal)
{
    if (index < this->number())
    {
        (*this->_signal)[index] = signal;
    }
}

void GoInput::remove(int index)
{
    this->_signal->remove(index);
}

QVector<GoSignal*>* GoInput::signal() const
{
    return this->_signal;
}

int GoInput::getSignalIndex(GoSignal* signal) const
{
    for (int i = 0; i < this->_signal->size(); ++i)
    {
        if (this->_signal->at(i) == signal)
        {
            return i;
        }
    }
    return -1;
}
