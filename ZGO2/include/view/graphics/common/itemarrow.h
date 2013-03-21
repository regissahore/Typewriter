#ifndef ITEMARROW_H
#define ITEMARROW_H
/**
 * 任意角度的箭头。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "qmath.h"
#include "itemdrawable.h"

class ItemArrow : public ItemDrawable
{
public:
    ItemArrow(QGraphicsItem *parent = 0);
    const QPoint end() const;
    void setEnd(const QPoint &end);
    void setEnd(const int x, const int y);
    QPoint sceneEnd();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

private:
    QPoint _end;
};

#endif // ITEMARROW_H
