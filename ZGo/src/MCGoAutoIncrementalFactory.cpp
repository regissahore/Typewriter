#include "MCGoAutoIncrementalFactory.h"

/**
 * 构造函数，将自动增长ID的初始值默认设置为1。
 */
MCGoAutoIncrementalFactory::MCGoAutoIncrementalFactory()
{
    this->setStartID(1);
}

/**
 * 设置自动增长的ID的初始值。
 * @param id 初始值。
 */
void MCGoAutoIncrementalFactory::setStartID(qint32 id)
{
    this->_id = id;
}

/**
 * 获取自动增长的ID，每调用一次该函数，内部ID增长1。
 */
qint32 MCGoAutoIncrementalFactory::id(void)
{
    return this->_id++;
}
