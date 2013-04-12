#ifndef ITEMMOVEABLE_H
#define ITEMMOVEABLE_H
/**
 * The basic moveable graphics item.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QGraphicsSceneMouseEvent>
#include "itemdrawable.h"

class ItemMoveable : public ItemDrawable
{
public:
    ItemMoveable(QGraphicsItem *parent = 0);
    bool moveable() const;
    virtual void startMove(QGraphicsSceneMouseEvent *event);
    virtual void move(QGraphicsSceneMouseEvent *event);
    virtual void stopMove(QGraphicsSceneMouseEvent *event);

private:
    QPointF _mousePressPosition;
};

#endif // ITEMMOVEABLE_H
