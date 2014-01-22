#ifndef ITEMGOTEXT_H
#define ITEMGOTEXT_H
#include "ItemMoveable.h"

class ItemGoText : public ItemMoveable
{
public:
    ItemGoText(QGraphicsItem *parent = 0);
    QString text() const;
    void setText(const QString text);
    bool isSelectable(float x, float y);
    bool isSelectable(float x, float y, float w, float h);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    ItemGoText* copy() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    QString _text;
};

#endif // ITEMGOTEXT_H
