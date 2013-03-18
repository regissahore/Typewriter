#ifndef ITEMMOVEABLE_H
#define ITEMMOVEABLE_H
/**
 * 基本的可以移动的图形。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QGraphicsSceneMouseEvent>
#include "itemdrawable.h"

class ItemMoveable : public ItemDrawable
{
public:
    ItemMoveable(QGraphicsItem *parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QPointF _mousePressPosition;
};

#endif // ITEMMOVEABLE_H
