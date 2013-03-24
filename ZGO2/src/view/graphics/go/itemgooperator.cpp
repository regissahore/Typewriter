#include "itemgooperator.h"
#include "itemarrow.h"
#include "gooperator.h"
#include "gooperatorfactory.h"
#include "itemgosignal.h"
#include "definationgotype.h"
#include "definationeditorselectiontype.h"

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

    int num = 1;
    if (this->model()->input()->number() > num)
    {
        num = this->model()->input()->number();
    }
    if (this->model()->output()->number() > num)
    {
        num = this->model()->output()->number();
    }
    int height = (num - 1) * 25;
    if (height < 50)
    {
        height = 50;
    }
    if ((height >> 1) < 75 && this->model()->subInput()->number() > 0)
    {
        height = 75 + (height >> 1);
        return QRectF(-75, -75, 150, height);
    }
    return QRectF(-75, -height * 0.5, 150, height);
}

bool ItemGOOperator::isSelected(float x, float y)
{
    return x > this->pos().x() - 25 &&
            x < this->pos().x() + 25 &&
            y > this->pos().y() - 25 &&
            y < this->pos().y() + 25;
}

bool ItemGOOperator::isSelected(float x, float y, float width, float height)
{
    float left, right, top, bottom;
    if (width >= 0)
    {
        left = x;
        right = x + width;
    }
    else
    {
        left = x + width;
        right = x;
    }
    if (height >= 0)
    {
        top = y;
        bottom = y + height;
    }
    else
    {
        top = y + height;
        bottom = y;
    }
    float thisLeft = this->pos().x() - 25;
    float thisRight = this->pos().x() + 25;
    float thisTop = this->pos().y() - 25;
    float thisBottom = this->pos().y() + 25;
    return left < thisLeft &&
            right > thisRight &&
            top < thisTop &&
            bottom > thisBottom;
}

/**
 * Start moving the item.
 * @param event Mouse event.
 */
void ItemGOOperator::move(QGraphicsSceneMouseEvent *event)
{
    this->ItemMoveable::move(event);
    QList<ItemGOSignal *> signal = this->getConnectedSignals();
    for (int i = 0; i < signal.size(); ++i)
    {
        signal[i]->updatePosition();
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
    painter->drawText(QRectF(-25, -25, 50, 50),
                      Qt::AlignHCenter | Qt::AlignVCenter,
                      QString("%1 - %2").arg(this->model()->type()).arg(this->model()->id()));
    painter->drawEllipse(QPoint(0, 0), 25, 25);
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
QList<ItemGOSignal *> ItemGOOperator::getConnectedSignals() const
{
    QList<ItemGOSignal*> signal;
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

void ItemGOOperator::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("operator");
    element.setAttribute("x", this->pos().x());
    element.setAttribute("y", this->pos().y());
    root.appendChild(element);
    this->model()->save(document, element);
    this->updateGraphic();
}

bool ItemGOOperator::tryOpen(QDomElement &root)
{
    if (root.tagName() != "operator")
    {
        return false;
    }
    float x = root.attribute("x", "0").toFloat();
    float y = root.attribute("y", "0").toFloat();
    this->setPos(x, y);
    QDomElement element = root.firstChildElement();
    GOOperator *model = new GOOperator();
    if (!model->tryOpen(element))
    {
        return false;
    }
    this->setModel(model);
    return true;
}
