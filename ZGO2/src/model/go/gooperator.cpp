#include "gooperator.h"

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
