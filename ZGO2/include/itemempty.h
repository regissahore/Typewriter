#ifndef ITEMEMPTY_H
#define ITEMEMPTY_H
/**
 * An unvisiable item.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "itemdrawable.h"

class ItemEmpty : public ItemDrawable
{
public:
    ItemEmpty(QGraphicsItem *parent = 0);
    bool isSelectable(float x, float y);
    bool isSelectable(float x, float y, float width, float height);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
};

#endif // ITEMEMPTY_H
