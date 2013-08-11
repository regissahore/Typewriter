#ifndef ITEMGOTEXT_H
#define ITEMGOTEXT_H
/**
 * The moveable text item.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "itemmoveable.h"

class ItemGOText : public ItemMoveable
{
public:
    ItemGOText(QGraphicsItem *parent = 0);
    QString text() const;
    void setText(const QString text);
    bool isSelectable(float x, float y);
    bool isSelectable(float x, float y, float w, float h);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    ItemGOText* copy() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    QString _text;
};

#endif // ITEMGOTEXT_H
