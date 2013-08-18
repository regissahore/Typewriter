#include <algorithm>
#include "itemgooperator.h"
#include "itemarrow.h"
#include "gooperator.h"
#include "gooperatorfactory.h"
#include "itemgosignal.h"
#include "definationgotype.h"
#include "definationeditorselectiontype.h"
#include "goinput.h"
#include "gooutput.h"
using namespace std;

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
    this->setIsHorizonFlip(false);
    this->setIsVerticalFlip(false);
    this->_isShowOutput = new QVector<bool>();
    this->_isShowOutput->push_back(true);
    this->setIsDrawParameter(false);
    this->setIsDrawName(false);
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
    delete this->_isShowOutput;
}

void ItemGOOperator::setModelType(const int type)
{
    this->_model = GOOperatorFactory::produce(type);
    this->setModel(this->_model);
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
    this->_inputSignal->clear();
    this->_subInputSignal->clear();
    this->_outputSignal->clear();
    if (this->isSource())
    {
        for (int i = 0; i < this->_outputArrows->size(); ++i)
        {
            this->_outputArrows->at(i)->setParentItem(0L);
            delete this->_outputArrows->at(i);
        }
        this->_outputArrows->clear();
        int number = this->model()->output()->number();
        double startY = - (number - 1) * 20.0;
        for (int i = 0; i < number; ++i)
        {
            ItemArrow *arrow = new ItemArrow(this);
            arrow->setPos(25.0, 0.0);
            arrow->setEnd(QPoint(50, startY));
            this->_outputArrows->push_back(arrow);
            startY += 40.0;
            this->_outputSignal->push_back(new QVector<ItemGOSignal*>());
        }
    }
    else
    {
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
        double startY = - (number - 1) * 20.0;
        for (int i = 0; i < number; ++i)
        {
            ItemArrow *arrow = new ItemArrow(this);
            arrow->setColor(QColor(Qt::darkRed));
            arrow->setPos(- 75, startY);
            double angle = atan2(-startY, 75);
            double dist = sqrt(startY * startY + 75 * 75);
            double x = (dist - 25.0) * cos(angle);
            double y = (dist - 25.0) * sin(angle);
            arrow->setEnd(QPoint(x, y));
            this->_inputArrows->push_back(arrow);
            startY += 40.0;
            this->_inputSignal->push_back(0L);
        }
        number = this->model()->output()->number();
        startY = - (number - 1) * 20.0;
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
            startY += 40.0;
            this->_outputSignal->push_back(new QVector<ItemGOSignal*>());
        }
        if (this->model()->subInput()->number() > 0)
        {
            ItemArrow *arrow = new ItemArrow(this);
            arrow->setColor(QColor(Qt::darkRed));
            arrow->setPos(0, -75);
            arrow->setEnd(QPoint(0, 50));
            this->_subInputArrows->push_back(arrow);
            this->_subInputSignal->push_back(0L);
        }
    }
    this->_isShowOutput->clear();
    for (int i = 0; i < this->model()->output()->number(); ++i)
    {
        this->_isShowOutput->push_back(true);
    }
    if (this->isHorizonFlip())
    {
        this->horizonFlip();
    }
    if (this->isVerticalFlip())
    {
        this->verticalFlip();
    }
    this->prepareGeometryChange();
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
    double y = -height * 0.5;
    if (this->model()->subInput()->number() > 0)
    {
        height = max(75.0, height * 0.5) + (height * 0.5);
        if (this->isVerticalFlip())
        {
            y = -25;
        }
        else
        {
            y = -75;
        }
    }
    return QRectF(-75, y, 150, height);
}

void ItemGOOperator::expandId(const int id)
{
    for (int i = 0; i < this->output()->size(); ++i)
    {
        for (int j = 0; j < this->output()->at(i)->size(); ++j)
        {
            this->output()->at(i)->at(j)->setId(id);
            this->output()->at(i)->at(j)->model()->setId(id);
            this->output()->at(i)->at(j)->update();
        }
    }
}

bool ItemGOOperator::isSelectable(float x, float y)
{
    return x > this->pos().x() - 25 &&
            x < this->pos().x() + 25 &&
            y > this->pos().y() - 25 &&
            y < this->pos().y() + 25;
}

bool ItemGOOperator::isSelectable(float x, float y, float width, float height)
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

bool ItemGOOperator::isHorizonFlip() const
{
    return this->_isHorizonFlip;
}

bool ItemGOOperator::isVerticalFlip() const
{
    return this->_isVerticalFlip;
}

void ItemGOOperator::setIsHorizonFlip(bool value)
{
    this->_isHorizonFlip = value;
}

void ItemGOOperator::setIsVerticalFlip(bool value)
{
    this->_isVerticalFlip = value;
}

void ItemGOOperator::horizonFlip()
{
    for (int i = 0; i < this->_inputArrows->size(); ++i)
    {
        this->_inputArrows->at(i)->setPos(-this->_inputArrows->at(i)->x(),
                                          this->_inputArrows->at(i)->y());
        this->_inputArrows->at(i)->setEnd(-this->_inputArrows->at(i)->end().x(),
                                          this->_inputArrows->at(i)->end().y());
    }
    for (int i = 0; i < this->_outputArrows->size(); ++i)
    {
        this->_outputArrows->at(i)->setPos(-this->_outputArrows->at(i)->x(),
                                           this->_outputArrows->at(i)->y());
        this->_outputArrows->at(i)->setEnd(-this->_outputArrows->at(i)->end().x(),
                                           this->_outputArrows->at(i)->end().y());
    }
    QList<ItemGOSignal *> signal = this->getConnectedSignals();
    for (int i = 0; i < signal.size(); ++i)
    {
        signal[i]->updatePosition();
    }
    this->update();
    this->prepareGeometryChange();
}

void ItemGOOperator::verticalFlip()
{
    for (int i = 0; i < this->_inputArrows->size(); ++i)
    {
        this->_inputArrows->at(i)->setPos(this->_inputArrows->at(i)->x(),
                                          -this->_inputArrows->at(i)->y());
        this->_inputArrows->at(i)->setEnd(this->_inputArrows->at(i)->end().x(),
                                          -this->_inputArrows->at(i)->end().y());
    }
    for (int i = 0; i < this->_subInputArrows->size(); ++i)
    {
        this->_subInputArrows->at(i)->setPos(this->_subInputArrows->at(i)->x(),
                                        -this->_subInputArrows->at(i)->y());
        this->_subInputArrows->at(i)->setEnd(this->_subInputArrows->at(i)->end().x(),
                                             -this->_subInputArrows->at(i)->end().y());
    }
    for (int i = 0; i < this->_outputArrows->size(); ++i)
    {
        this->_outputArrows->at(i)->setPos(this->_outputArrows->at(i)->x(),
                                           -this->_outputArrows->at(i)->y());
        this->_outputArrows->at(i)->setEnd(this->_outputArrows->at(i)->end().x(),
                                           -this->_outputArrows->at(i)->end().y());
    }
    QList<ItemGOSignal *> signal = this->getConnectedSignals();
    for (int i = 0; i < signal.size(); ++i)
    {
        signal[i]->updatePosition();
    }
    this->update();
    this->prepareGeometryChange();
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
    painter->setPen(Qt::SolidLine);
    painter->setPen(this->_color);
    painter->setBrush(Qt::NoBrush);
    QFont font;
    font.setPixelSize(16);
    painter->setFont(font);
    for (int i = 0; i < this->model()->output()->number(); ++i)
    {
        this->_outputArrows->at(i)->setVisible(this->isShowOutput()->at(i));
    }
    if (this->isSource())
    {
        painter->drawText(QRectF(-100, -100, 200, 200), Qt::AlignHCenter | Qt::AlignVCenter, QString("%1 - %2").arg(this->model()->type()).arg(this->model()->id()));
        QPoint points[3];
        if (this->isHorizonFlip())
        {
            points[0].setX(-25);
            points[0].setY(0);
            points[1].setX(22);
            points[1].setY(-25);
            points[2].setX(22);
            points[2].setY(25);
        }
        else
        {
            points[0].setX(25);
            points[0].setY(0);
            points[1].setX(-22);
            points[1].setY(-25);
            points[2].setX(-22);
            points[2].setY(25);
        }
        painter->drawPolygon(points, 3);
    }
    else
    {
        painter->drawText(QRectF(-100, -100, 200, 200),
                          Qt::AlignHCenter | Qt::AlignVCenter,
                          QString("%1 - %2").arg(this->model()->type()).arg(this->model()->id()));
        painter->drawEllipse(QPoint(0, 0), 25, 25);
    }
}

/**
 * Get the input position.
 * @param index The input index.
 */
QPoint ItemGOOperator::getInputPosition(int index)
{
    return QPoint(this->_inputArrows->at(index)->pos().x(),
                  this->_inputArrows->at(index)->pos().y());
}

/**
 * Get the sub input position.
 * @param index The sub input index.
 */
QPoint ItemGOOperator::getSubInputPosition(int index)
{
    return QPoint(this->_subInputArrows->at(index)->pos().x(),
                  this->_subInputArrows->at(index)->pos().y());
}

/**
 * Get the output position.
 * @param index The output index.
 */
QPoint ItemGOOperator::getOutputPosition(int index)
{
    return QPoint(this->_outputArrows->at(index)->pos().x() + this->_outputArrows->at(index)->end().x(),
                  this->_outputArrows->at(index)->pos().y() + this->_outputArrows->at(index)->end().y());
}

QPoint ItemGOOperator::getInputDeepPosition(int index)
{
    return QPoint(this->_inputArrows->at(index)->pos().x() + this->_inputArrows->at(index)->end().x(),
                  this->_inputArrows->at(index)->pos().y() + this->_inputArrows->at(index)->end().y());
}

QPoint ItemGOOperator::getSubInputDeepPosition(int index)
{
    return QPoint(this->_subInputArrows->at(index)->pos().x() + this->_subInputArrows->at(index)->end().x(),
                  this->_subInputArrows->at(index)->pos().y() + this->_subInputArrows->at(index)->end().y());
}

QVector<ItemGOSignal*>* ItemGOOperator::input() const
{
    return this->_inputSignal;
}

QVector<ItemGOSignal*>* ItemGOOperator::subInput() const
{
    return this->_subInputSignal;
}

QVector<QVector<ItemGOSignal*>*>* ItemGOOperator::output() const
{
    return this->_outputSignal;
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
            this->_inputArrows->at(index)->setColor(QColor(Qt::black));
        }
        break;
    case DefinationGOType::GO_OPERATOR_SUBINPUT:
        if (index >= 0 && index < this->model()->subInput()->number())
        {
            (*this->_subInputSignal)[index] = signal;
            this->_subInputArrows->at(index)->setColor(QColor(Qt::black));
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
            this->_inputArrows->at(index)->setColor(QColor(Qt::darkRed));
        }
        break;
    case DefinationGOType::GO_OPERATOR_SUBINPUT:
        if (index >= 0 && index < this->model()->subInput()->number())
        {
            (*this->_subInputSignal)[index] = 0L;
            this->_subInputArrows->at(index)->setColor(QColor(Qt::darkRed));
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

QVector<bool>* ItemGOOperator::isShowOutput() const
{
    return this->_isShowOutput;
}

bool ItemGOOperator::isDrawParameter() const
{
    return this->_isDrawParameter;
}

void ItemGOOperator::setIsDrawParameter(const bool value)
{
    this->_isDrawParameter = value;
}

bool ItemGOOperator::isDrawName() const
{
    return this->_isDrawName;
}

void ItemGOOperator::setIsDrawName(const bool value)
{
    this->_isDrawName = value;
}

void ItemGOOperator::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("operator");
    element.setAttribute("x", this->pos().x());
    element.setAttribute("y", this->pos().y());
    element.setAttribute("type", this->model()->type());
    element.setAttribute("horizon", this->isHorizonFlip());
    element.setAttribute("vertical", this->isVerticalFlip());
    element.setAttribute("parameter", this->isDrawParameter());
    element.setAttribute("name", this->isDrawName());
    for (int i = 0; i < this->model()->output()->number(); ++i)
    {
        element.setAttribute(QString("show_output_%1").arg(i), this->isShowOutput()->at(i));
    }
    root.appendChild(element);
    this->model()->save(document, element);
}

bool ItemGOOperator::tryOpen(QDomElement &root)
{
    if (root.tagName() != "operator")
    {
        return false;
    }
    this->setX(root.attribute("x", "0").toFloat());
    this->setY(root.attribute("y", "0").toFloat());
    this->setIsHorizonFlip(root.attribute("horizon", "0").toInt());
    this->setIsVerticalFlip(root.attribute("vertical", "0").toInt());
    this->setIsDrawParameter(root.attribute("parameter", "0").toInt());
    this->setIsDrawName(root.attribute("name", "0").toInt());
    QDomElement element = root.firstChildElement();
    GOOperator *model = new GOOperator();
    if (!model->tryOpen(element))
    {
        return false;
    }
    this->setModel(model);
    for (int i = 0; i < this->model()->output()->number(); ++i)
    {
        (*this->isShowOutput())[i] = root.attribute(QString("show_output_%1").arg(i), "1").toInt();
    }
    return true;
}

bool ItemGOOperator::isSource() const
{
    return this->model()->type() == GOOperatorFactory::Operator_Type_4 ||
            this->model()->type() == GOOperatorFactory::Operator_Type_5;
}
