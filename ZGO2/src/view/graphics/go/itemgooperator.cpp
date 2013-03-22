#include "itemgooperator.h"
#include "itemarrow.h"
#include "gooperator.h"
#include "gooperatorfactory.h"
#include "itemgosignal.h"
#include "definationgotype.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOOperator::ItemGOOperator(QGraphicsItem *parent) : ItemMoveable(parent)
{
    this->_inputArrows = new QVector<ItemArrow*>();
    this->_subInputArrows = new QVector<ItemArrow*>();
    this->_outputArrows = new QVector<ItemArrow*>();
    this->_inputSignal = new QVector<ItemGOSignal*>();
    this->_subInputSignal = new QVector<ItemGOSignal*>();
    this->_outputSignal = new QVector<QVector<ItemGOSignal*>*>();
    this->TypedItem::setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR);
}

/**
 * Destructor.
 */
ItemGOOperator::~ItemGOOperator()
{
    this->_inputArrows->clear();
    this->_subInputArrows->clear();
    this->_outputArrows->clear();
    this->setParentItem(0L);
    this->_inputSignal->clear();
    this->_subInputSignal->clear();
    for (int i = 0; i < this->_outputSignal->size(); ++i)
    {
        this->_outputSignal->at(i)->clear();
    }
    this->_outputSignal->clear();
}

/**
 * 获得GO操作符数据模型。
 * @return 数据模型。
 */
GOOperator* ItemGOOperator::model() const
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
        this->_inputSignal->push_back(0L);
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
        this->_outputSignal->push_back(new QVector<ItemGOSignal*>());
    }
    if (this->model()->subInput()->number() > 0)
    {
        ItemArrow *arrow = new ItemArrow(this);
        arrow->setPos(0, -75);
        arrow->setEnd(QPoint(0, 50));
        this->_subInputArrows->push_back(arrow);
        this->_subInputSignal->push_back(0L);
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
    if ((height >> 1) < 75)
    {
        height = 75 + (height >> 1);
        return QRectF(-75, -75, 150, height);
    }
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
        for (int i = 0; i < this->_inputSignal->size(); ++i)
        {
            if (this->_inputSignal->at(i) != 0L)
            {
                this->_inputSignal->at(i)->updatePosition();
            }
        }
        for (int i = 0; i < this->_subInputSignal->size(); ++i)
        {
            if (this->_subInputSignal->at(i) != 0L)
            {
                this->_subInputSignal->at(i)->updatePosition();
            }
        }
        for (int i = 0; i < this->_outputSignal->size(); ++i)
        {
            if (this->_outputSignal->size() > 0)
            {
                for (int j = 0; j < this->_outputSignal->at(i)->size(); ++j)
                {
                    this->_outputSignal->at(i)->at(j)->updatePosition();
                }
            }
        }
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

/**
 * Get the input position.
 * @param index The input index.
 */
QPoint ItemGOOperator::getInputPosition(int index)
{
    int number = this->model()->input()->number();
    if (index < 0 || index >= number)
    {
        return QPoint(0, 0);
    }
    int height = (number - 1) * 25;
    int y = - (height >> 1) + index * 25;
    return QPoint(-75, y);
}

/**
 * Get the sub input position.
 * @param index The sub input index.
 */
QPoint ItemGOOperator::getSubInputPosition(int index)
{
    Q_UNUSED(index);
    return QPoint(0, -75);
}

/**
 * Get the output position.
 * @param index The output index.
 */
QPoint ItemGOOperator::getOutputPosition(int index)
{
    int number = this->model()->output()->number();
    if (index < 0 || index >= number)
    {
        return QPoint(0, 0);
    }
    int height = (number - 1) * 25;
    int y = - (height >> 1) + index * 25;
    return QPoint(75, y);
}

/**
 * Set the signal to one input or output.
 * @param signal The GO signal.
 * @param type The connection type. @see DefinationGOType
 * @param index The index of the connection.
 */
void ItemGOOperator::setSignal(ItemGOSignal *signal, int type, int index)
{
    switch (type)
    {
    case DefinationGOType::GO_OPERATOR_INPUT:
        if (index >= 0 && index < this->model()->input()->number())
        {
            (*this->_inputSignal)[index] = signal;
        }
        break;
    case DefinationGOType::GO_OPERATOR_SUBINPUT:
        if (index >= 0 && index < this->model()->subInput()->number())
        {
            (*this->_subInputSignal)[index] = signal;
        }
        break;
    case DefinationGOType::GO_OPERATOR_OUTPUT:
        if (index >= 0 && index < this->model()->output()->number())
        {
            this->_outputSignal->at(index)->push_back(signal);
        }
        break;
    }
}

/**
 * Remove the signal to one input or output.
 * @param signal The GO signal.
 * @param type The connection type. @see DefinationGOType
 * @param index The index of the connection.
 */
void ItemGOOperator::removeSignal(ItemGOSignal *signal, int type, int index)
{
    switch (type)
    {
    case DefinationGOType::GO_OPERATOR_INPUT:
        if (index >= 0 && index < this->model()->input()->number())
        {
            (*this->_inputSignal)[index] = 0L;
        }
        break;
    case DefinationGOType::GO_OPERATOR_SUBINPUT:
        if (index >= 0 && index < this->model()->subInput()->number())
        {
            (*this->_subInputSignal)[index] = 0L;
        }
        break;
    case DefinationGOType::GO_OPERATOR_OUTPUT:
        if (index >= 0 && index < this->model()->output()->number())
        {
            for (int i = 0; i < this->_outputSignal->at(index)->size(); ++i)
            {
                if (this->_outputSignal->at(index)->at(i) == signal)
                {
                    this->_outputSignal->at(index)->remove(i);
                }
            }
        }
        break;
    }
}

/**
 * Get all signals connected to the operator.
 * @return The vector of signal.
 */
QVector<ItemGOSignal*> ItemGOOperator::getConnectedSignals() const
{
    QVector<ItemGOSignal*> signal;
    for (int i = 0; i < this->_inputSignal->size(); ++i)
    {
        if (this->_inputSignal->at(i) != 0L)
        {
            signal.push_back(this->_inputSignal->at(i));
        }
    }
    for (int i = 0; i < this->_subInputSignal->size(); ++i)
    {
        if (this->_subInputSignal->at(i) != 0L)
        {
            signal.push_back(this->_subInputSignal->at(i));
        }
    }
    for (int i = 0; i < this->_outputSignal->size(); ++i)
    {
        for (int j = 0; j < this->_outputSignal->at(i)->size(); ++j)
        {
            signal.push_back((this->_outputSignal->at(i)->at(j)));
        }
    }
    return signal;
}
