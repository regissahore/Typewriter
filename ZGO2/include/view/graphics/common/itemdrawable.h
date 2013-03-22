#ifndef ITEMDRAWABLE_H
#define ITEMDRAWABLE_H
/**
 * 基本的可绘制图形。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <qmath.h>
#include <QPainter>
#include <QGraphicsItem>
#include "typeditem.h"
#include "definationeditorselectiontype.h"

const double PI = acos(-1.0);

class ItemDrawable : public QGraphicsItem, public TypedItem
{
public:
    ItemDrawable(QGraphicsItem *parent = 0);
    ~ItemDrawable();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    QSize size() const;
    qreal width() const;
    qreal height() const;
    void setWidth(qreal width);
    void setHeight(qreal height);
    void setSize(qreal width, qreal height);
    virtual bool moveable() const;

private:
    qreal _width;
    qreal _height;
};

#endif // ITEMDRAWABLE_H
