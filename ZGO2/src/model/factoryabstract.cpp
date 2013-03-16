#include "model/factoryabstract.h"

/**
 * 构造函数，ID默认从0开始增长。
 */
FactoryAbstract::FactoryAbstract()
{
    this->setId(0);
}

/**
 * 设置自动增长的ID的初始值。
 * @param id ID。
 */
void FactoryAbstract::setId(int id)
{
    this->_id = id;
}

/**
 * 获取自动增长的ID。
 * @return ID。
 */
int FactoryAbstract::id()
{
    return this->_id++;
}
