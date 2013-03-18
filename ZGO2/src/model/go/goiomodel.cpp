#include "goiomodel.h"

/**
 * 构造函数。
 */
GOIOModel::GOIOModel()
{
    this->_signal = new QVector<GOSignal*>();
}

/**
 * 获得信号流的数量。
 * @return 信号流的数量。
 */
int GOIOModel::number() const
{
    return this->_signal->size();
}

/**
 * 设置信号流的数量。如果数量比原有值多，则会插入空的信号流；
 * 如果数量比原有值少，则会删除最末端的信号流。
 * @param num 信号流的数量
 */
void GOIOModel::setNumber(int num)
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
void GOIOModel::add(GOSignal *signal)
{
    this->_signal->push_back(signal);
}

/**
 * 设置信号流。
 * @param index 信号流位置，下标从0开始。
 * @param signal 信号流。
 */
void GOIOModel::set(int index, GOSignal *signal)
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
void GOIOModel::remove(int index)
{
    this->_signal->remove(index);
}

/**
 * 返回信号流的集合。
 * @return 信号流集合。
 */
QVector<GOSignal*>* GOIOModel::signal() const
{
    return this->_signal;
}

