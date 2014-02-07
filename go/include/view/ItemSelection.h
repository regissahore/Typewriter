#ifndef ITEMSELECTION_H
#define ITEMSELECTION_H
#include <QPainter>
#include "ItemMoveable.h"

class ItemSelection : public ItemMoveable
{
public:
    ItemSelection(QGraphicsItem *parent = 0);
    const QPoint end() const;
    int left() const;
    int right() const;
    int top() const;
    int bottom() const;
    bool isInside(int x, int y) const;
    void setEnd(const QPoint &end);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

private:
    QPoint _end;
};

#endif // ITEMSELECTION_H
