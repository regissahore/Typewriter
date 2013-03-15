#ifndef ITEMGOSOURCE_H
#define ITEMGOSOURCE_H
/**
 * GO操作符中的信号发生器。
 * @author ZHG <CyberZHG@gmail.com>
 */

#include "model/identifieditem.h"
#include "view/itemgooperator.h"

class ItemGOSource : public ItemGOOperator
{
public:
    ItemGOSource();
    void setModel(GOOperator *model);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
};

#endif // ITEMGOSOURCE_H
