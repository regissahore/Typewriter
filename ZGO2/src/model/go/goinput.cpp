#include "goinput.h"
#include "gosignal.h"

/**
 * 构造函数。
 */
GOInput::GOInput()
{
    this->_signal = new QVector<GOSignal*>();
}

GOInput::~GOInput()
{
    this->_signal->clear();
    delete this->_signal;
}

/**
 * 获得信号流的数量。
 * @return 信号流的数量。
 */
int GOInput::number() const
{
    return this->_signal->size();
}

/**
 * 设置信号流的数量。如果数量比原有值多，则会插入空的信号流；
 * 如果数量比原有值少，则会删除最末端的信号流。
 * @param num 信号流的数量
 */
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

/**
 * 添加新的信号流。
 * @param signal 信号流。
 */
void GOInput::add(GOSignal *signal)
{
    this->_signal->push_back(signal);
}

/**
 * 设置信号流。
 * @param index 信号流位置，下标从0开始。
 * @param signal 信号流。
 */
void GOInput::set(int index, GOSignal *signal)
{
    if (index < this->number())
    {
        (*this->_signal)[index] = signal;
    }
}

/**
 * 删除指定编号的信号流。
 * @param index 信号流位置，下标从0开始。
 */
void GOInput::remove(int index)
{
    this->_signal->remove(index);
}

/**
 * 返回信号流的集合。
 * @return 信号流集合。
 */
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
