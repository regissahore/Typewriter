#ifndef ITEMGOOPERATOR_H
#define ITEMGOOPERATOR_H
/**
 * 基本的可绘制的GO操作符。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "itemmoveable.h"
#include "itemarrow.h"
#include "gooperator.h"
#include "gooperatorfactory.h"

class ItemGOOperator : public ItemMoveable
{
public:
    ItemGOOperator(QGraphicsItem *parent = 0);
    ~ItemGOOperator();
    const GOOperator* model() const;
    void setModel(GOOperator *model);
    void updateGraphic();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

protected:
    QVector<ItemArrow*> *_inputArrows; /** 主输入箭头。 */
    QVector<ItemArrow*> *_subInputArrows; /** 次输入箭头。 */
    QVector<ItemArrow*> *_outputArrows; /** 输出箭头。 */
    GOOperator *_model; /** GO操作符模型。 */
};

#endif // ITEMGOOPERATOR_H
