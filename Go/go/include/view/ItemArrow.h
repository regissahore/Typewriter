#ifndef ITEMARROW_H
#define ITEMARROW_H
#include "ItemDrawable.h"

class ItemArrow : public ItemDrawable
{
public:
    ItemArrow(QGraphicsItem *parent = 0);
    const QPoint end() const;
    void setEnd(const QPoint &end);
    void setEnd(const int x, const int y);
    QPoint sceneEnd();
    bool isShowArrow() const;
    void setIsShowArrow(const bool value);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

private:
    QPoint _end;
    bool _isShowArrow;
};

#endif // ITEMARROW_H
