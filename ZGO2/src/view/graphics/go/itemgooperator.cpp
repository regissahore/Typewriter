#include "itemgooperator.h"

/**
 * 构造函数。
 */
ItemGOOperator::ItemGOOperator(QGraphicsItem *parent) : ItemMoveable(parent)
{
    this->_inputArrows = new QVector<ItemArrow*>();
    this->_subInputArrows = new QVector<ItemArrow*>();
    this->_outputArrows = new QVector<ItemArrow*>();
}

/**
 * 析构函数。
 */
ItemGOOperator::~ItemGOOperator()
{
    this->_inputArrows->clear();
    this->_subInputArrows->clear();
    this->_outputArrows->clear();
}

/**
 * 获得GO操作符数据模型。
 * @return 数据模型。
 */
const GOOperator* ItemGOOperator::model() const
{
    return this->_model;
}

/**
 * 设置GO操作符数据模型。
 * @param model 数据模型。
 */
void ItemGOOperator::setModel(GOOperator *model)
{
    this->_model = model;
    this->childItems().clear();
    this->_inputArrows->clear();
    this->_subInputArrows->clear();
    this->_outputArrows->clear();
    int number = this->model()->input()->number();
    double startY = - (number - 1) * 12.5;
    for (int i = 0; i < number; ++i)
    {
        ItemArrow *arrow = new ItemArrow(this);
        arrow->setPos(- 75, startY);
        double angle = atan2(-startY, 75);
        double dist = sqrt(startY * startY + 75 * 75);
        double x = (dist - 25.0) * cos(angle);
        double y = (dist - 25.0) * sin(angle);
        arrow->setEnd(QPoint(x, y));
        this->_inputArrows->push_back(arrow);
        startY += 25.0;
    }
    number = this->model()->output()->number();
    startY = - (number - 1) * 12.5;
    for (int i = 0; i < number; ++i)
    {
        ItemArrow *arrow = new ItemArrow(this);
        double angle = atan2(startY, 75);
        arrow->setPos(25.0 * cos(angle), 25.0 * sin(angle));
        double dist = sqrt(startY * startY + 75 * 75);
        double x = (dist - 25.0) * cos(angle);
        double y = (dist - 25.0) * sin(angle);
        arrow->setEnd(QPoint(x, y));
        this->_outputArrows->push_back(arrow);
        startY += 25.0;
    }
    if (this->model()->subInput())
    {
        ItemArrow *arrow = new ItemArrow(this);
        arrow->setPos(0, -75);
        arrow->setEnd(QPoint(0, 50));
        this->_subInputArrows->push_back(arrow);
    }
}

/**
 * Update the graphics view when the model is modified.
 */
void ItemGOOperator::updateGraphic()
{
    this->setModel(this->_model);
}

/**
 * 获得边界。
 * @return 边界。
 */
QRectF ItemGOOperator::boundingRect() const
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
    return QRectF(-75, -height * 0.5, 150, height);*/
    return QRectF(-25, -25, 50, 50);
}

/**
 * 绘制图形。
 * @param painter 画笔。
 * @param item 配置。
 * @param widget 父窗体。
 */
void ItemGOOperator::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(QRectF(-25, -25, 50, 50), Qt::AlignHCenter | Qt::AlignVCenter, QString("%1 - %2").arg(this->model()->type()).arg(this->model()->id()));
    painter->drawText(QRectF(-1000, 35, 2000, 40), Qt::AlignHCenter | Qt::AlignTop, this->model()->name());
    painter->drawEllipse(QPoint(0, 0), 25, 25);
}

