#ifndef ITEMDRAWABLE_H
#define ITEMDRAWABLE_H
/**
 * The basic abstract drawable item.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <qmath.h>
#include <QPainter>
#include <QGraphicsItem>
#include "typeditem.h"

const double PI = acos(-1.0);

class ItemDrawable : public QGraphicsItem, public TypedItem
{
public:
    ItemDrawable(QGraphicsItem *parent = 0);
    virtual ~ItemDrawable();
    virtual bool isSelected(float x, float y);
    virtual bool isSelected(float x, float y, float width, float height);
    virtual bool moveable() const;
};

#endif // ITEMDRAWABLE_H
