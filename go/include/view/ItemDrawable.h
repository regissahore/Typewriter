#ifndef ITEMDRAWABLE_H
#define ITEMDRAWABLE_H
#include <qmath.h>
#include <QPainter>
#include <QGraphicsItem>
#include "TypedItem.h"
#include "DomItem.h"

const double PI = acos(-1.0);

class ItemDrawable : public QGraphicsItem, public TypedItem, public DomItem
{
public:
    ItemDrawable(QGraphicsItem *parent = 0);
    virtual ~ItemDrawable();
    virtual bool isSelectable(float x, float y);
    virtual bool isSelectable(float x, float y, float width, float height);
    virtual bool moveable() const;
    void setColor(QColor color);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QColor _color;
};

#endif // ITEMDRAWABLE_H
