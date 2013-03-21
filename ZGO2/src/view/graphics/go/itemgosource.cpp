#include "itemgosource.h"

/**
 * 构造函数。
 */
ItemGOSource::ItemGOSource(QGraphicsItem *parent) : ItemGOOperator(parent)
{
}

/**
 * 设置GO操作符数据模型。
 * @param model 数据模型。
 */
void ItemGOSource::setModel(GOOperator *model)
{
    this->_model = model;
    this->childItems().clear();
    this->_outputArrows->clear();
    int number = this->model()->output()->number();
    double startY = - (number - 1) * 12.5;
    for (int i = 0; i < number; ++i)
    {
        ItemArrow *arrow = new ItemArrow(this);
        arrow->setPos(25.0, 0.0);
        arrow->setEnd(QPoint(50, startY));
        this->_outputArrows->push_back(arrow);
        startY += 25.0;
    }
}

/**
 * 获得边界。
 * @return 边界。
 */
QRectF ItemGOSource::boundingRect() const
{
    /*int num = 3;
    if (this->model()->input()->number() > num)
    {
        num = this->model()->input()->number();
    }
    if (this->model()->output()->number() > num)
    {
        num = this->model()->output()->number();
    }
    int height = (num - 1) * 25 + 50;
    return QRectF(-22, -height * 0.5, 97, height);*/
    return QRectF(-25, -25, 50, 50);
}

/**
 * 绘制图形。
 * @param painter 画笔。
 * @param item 配置。
 * @param widget 父窗体。
 */
void ItemGOSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(QRectF(-25, -25, 47, 50), Qt::AlignHCenter | Qt::AlignVCenter, QString("%1 - %2").arg(this->model()->type()).arg(this->model()->id()));
    painter->drawText(QRectF(-1000, 35, 2000, 40), Qt::AlignHCenter | Qt::AlignTop, this->model()->name());
    QPoint points[3];
    points[0].setX(25);
    points[0].setY(0);
    points[1].setX(-22);
    points[1].setY(-25);
    points[2].setX(-22);
    points[2].setY(25);
    painter->drawPolygon(points, 3);
}
