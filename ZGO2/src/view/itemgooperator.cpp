#include "view/itemgooperator.h"

/**
 * 构造函数。
 */
ItemGOOperator::ItemGOOperator()
{
}

/**
 * 获得GO操作符数据模型。
 * @return 数据模型。
 */
const GOOperator* ItemGOOperator::model() const
{
    return this->_model;
}

/**
 * 设置GO操作符数据模型。
 * @param model 数据模型。
 */
void ItemGOOperator::setModel(GOOperator *model)
{
    this->_model = model;
}
