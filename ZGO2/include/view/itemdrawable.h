#ifndef ITEMDRAWABLE_H
#define ITEMDRAWABLE_H
/**
 * 基本的可绘制图形。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QPainter>
#include <QGraphicsItem>

class ItemDrawable : public QGraphicsItem
{
public:
    ItemDrawable();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    QSize size() const;
    qreal width() const;
    qreal height() const;
    void setWidth(qreal width);
    void setHeight(qreal height);
    void setSize(qreal width, qreal height);

private:
    qreal _width;
    qreal _height;
};

#endif // ITEMDRAWABLE_H
