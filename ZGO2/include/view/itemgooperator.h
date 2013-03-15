#ifndef ITEMGOOPERATOR_H
#define ITEMGOOPERATOR_H
/**
 * 基本的可绘制的GO操作符。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "view/itemmoveable.h"
#include "model/gooperator.h"

class ItemGOOperator : public ItemMoveable
{
public:
    ItemGOOperator();
    const GOOperator* model() const;
    void setModel(GOOperator *model);

private:
    GOOperator *_model; /** GO操作符模型。 */
};

#endif // ITEMGOOPERATOR_H
