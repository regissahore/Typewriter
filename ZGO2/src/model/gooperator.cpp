#include "model/gooperator.h"

/**
 * 构造函数。
 */
GOOperator::GOOperator()
{
    this->_input = new GOIOModel();
    this->_subInput = new GOIOModel();
    this->_output = new GOIOModel();
}

/**
 * 返回当前操作符的类型。
 * @return 操作符类型。
 */
qint32 GOOperator::type() const
{
    return this->_type;
}

/**
 * 设置当前操作符的类型。
 * @param type 操作符类型。
 */
void GOOperator::setType(const int type)
{
    this->_type = type;
}

/**
 * 返回主输入信号流。
 * @return 主输入信号流。
 */
GOIOModel *GOOperator::input() const
{
    return this->_input;
}

/**
 * 返回次输入信号流。
 * @return 次输入信号流。
 */
GOIOModel *GOOperator::subInput() const
{
    return this->_subInput;
}

/**
 * 返回输出信号流。
 * @return 输出信号流。
 */
GOIOModel *GOOperator::output() const
{
    return this->_output;
}
