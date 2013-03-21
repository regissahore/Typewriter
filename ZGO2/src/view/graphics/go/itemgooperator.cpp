#include "itemgooperator.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperator::ItemGOOperator(QGraphicsItem *parent) : ItemMoveable(parent)
{
    this->_inputArrows = new QVector<ItemArrow*>();
    this->_subInputArrows = new QVector<ItemArrow*>();
    this->_outputArrows = new QVector<ItemArrow*>();
    this->TypedItem::setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR);
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
    for (int i = 0; i < this->_inputArrows->size(); ++i)
    {
        this->_inputArrows->at(i)->setParentItem(0L);
        delete this->_inputArrows->at(i);
    }
    this->_inputArrows->clear();
    for (int i = 0; i < this->_subInputArrows->size(); ++i)
    {
        this->_subInputArrows->at(i)->setParentItem(0L);
        delete this->_subInputArrows->at(i);
    }
    this->_subInputArrows->clear();
    for (int i = 0; i < this->_outputArrows->size(); ++i)
    {
        this->_outputArrows->at(i)->setParentItem(0L);
        delete this->_outputArrows->at(i);
    }
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
    if (this->model()->subInput()->number() > 0)
    {
        ItemArrow *arrow = new ItemArrow(this);
        arrow->setPos(0, -75);
        arrow->setEnd(QPoint(0, 50));
        this->_subInputArrows->push_back(arrow);
    }
    this->prepareGeometryChange();
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
    int num = 3;
    if (this->model()->input()->number() > num)
    {
        num = this->model()->input()->number();
    }
    if (this->model()->output()->number() > num)
    {
        num = this->model()->output()->number();
    }
    int height = (num - 1) * 25 + 50;
    return QRectF(-75, -height * 0.5, 150, height);
}

/**
 * Start moving the item.
 * @param event Mouse event.
 */
void ItemGOOperator::startMove(QGraphicsSceneMouseEvent *event)
{
    if (this->isInside(event->scenePos().x(), event->scenePos().y()))
    {
        this->ItemMoveable::startMove(event);
    }
}

/**
 * Start moving the item.
 * @param event Mouse event.
 */
void ItemGOOperator::move(QGraphicsSceneMouseEvent *event)
{
    if (this->isInside(event->scenePos().x(), event->scenePos().y()))
    {
        this->ItemMoveable::move(event);
    }
}

/**
 * Start moving the item.
 * @param event Mouse event.
 */
void ItemGOOperator::stopMove(QGraphicsSceneMouseEvent *event)
{
    if (this->isInside(event->scenePos().x(), event->scenePos().y()))
    {
        this->ItemMoveable::stopMove(event);
    }
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

/**
 * Whether the cursor is inside the moving area.
 * @param x The scene x position.
 * @param y The scene y position.
 * @return Returns true if it is inside, otherwise false.
 */
bool ItemGOOperator::isInside(int x, int y)
{
    int ox = x - this->pos().x();
    int oy = y - this->pos().y();
    return ox > -25 && ox < 25 && oy > -25 && oy < 25;
}
