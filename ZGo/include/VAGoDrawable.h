#ifndef VAGODRAWABLE_H
#define VAGODRAWABLE_H
/**
 * 基本的可绘制单元。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QRectF>
#include <QWidget>
#include <QGraphicsItem>

class VAGoDrawable : QGraphicsItem
{
public:
    VAGoDrawable();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paint(QPainter *painter);
    qreal width(void) const;
    qreal height(void) const;
    QSize size(void) const;
    void setWidth(qreal width);
    void setHeight(qreal height);
    void setSize(qreal width, qreal height);
    void setSize(QSize size);
    bool isFocus(void) const;
    void setFocus(bool value);

protected:
    qreal _width; /** 当前图形的长度。 */
    qreal _height; /** 当前图形的宽度。 */
    bool _focus; /** 当前是否处于选中状态。 */
};

#endif // VAGODRAWABLE_H
