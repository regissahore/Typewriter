#include "goinput.h"
#include "gosignal.h"

GOInput::GOInput()
{
    this->_signal = new QVector<GOSignal*>();
}

GOInput::~GOInput()
{
    this->_signal->clear();
    delete this->_signal;
}

int GOInput::number() const
{
    return this->_signal->size();
}

void GOInput::setNumber(int num)
{
    if (this->number() < num)
    {
        num = num - this->number();
        while (num--)
        {
            this->add(0L);
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

void GOInput::add(GOSignal *signal)
{
    this->_signal->push_back(signal);
}

void GOInput::set(int index, GOSignal *signal)
{
    if (index < this->number())
    {
        (*this->_signal)[index] = signal;
    }
}

void GOInput::remove(int index)
{
    this->_signal->remove(index);
}

QVector<GOSignal*>* GOInput::signal() const
{
    return this->_signal;
}

int GOInput::getSignalIndex(GOSignal* signal) const
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
