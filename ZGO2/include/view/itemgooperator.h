#ifndef ITEMGOOPERATOR_H
#define ITEMGOOPERATOR_H
/**
 * 基本的可绘制的GO操作符。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "view/itemmoveable.h"
#include "view/itemarrow.h"
#include "model/gooperator.h"

class ItemGOOperator : public ItemMoveable
{
public:
    ItemGOOperator(QGraphicsItem *parent = 0);
    ~ItemGOOperator();
    const GOOperator* model() const;
    void setModel(GOOperator *model);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

protected:
    QVector<ItemArrow*> *_inputArrows;
    QVector<ItemArrow*> *_subInputArrows;
    QVector<ItemArrow*> *_outputArrows;

private:
    GOOperator *_model; /** GO操作符模型。 */
};

#endif // ITEMGOOPERATOR_H
