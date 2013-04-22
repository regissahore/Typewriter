#include <QtAlgorithms>
#include "itemgosignal.h"
#include "itemgooperator.h"
#include "gooperator.h"
#include "definationgotype.h"
#include "definationeditorselectiontype.h"
#include "gosignalfactory.h"

/**
 * Constructor.
 * @param parent The parent graphics item.
 */
ItemGOSignal::ItemGOSignal(QGraphicsItem *parent) : ItemDrawable(parent)
{
    this->_start = new SignalConnection();
    this->_end = new SignalConnection();
    this->_start->op = 0L;
    this->_end->op = 0L;
    this->setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL);
    this->_model = GOSignalFactory::produce();
}

/**
 * Destructor.
 */
ItemGOSignal::~ItemGOSignal()
{
    this->setParentItem(0L);
    delete this->_model;
    GOSignalFactory::setID(GOSignalFactory::currentID() - 1);
    delete this->_start;
    delete this->_end;
}

QRectF ItemGOSignal::boundingRect() const
{
    float left, right, top, bottom;
    if (this->_endPos.x() < 0)
    {
        left = this->_endPos.x() - 2;
        right = 2;
    }
    else
    {
        left = -2;
        right = this->_endPos.x() + 2;
    }
    if (this->_endPos.y() < 0)
    {
        top = this->_endPos.y() - 2;
        bottom = 2;
    }
    else
    {
        top = -2;
        bottom = this->_endPos.y() + 2;
    }
    return QRectF(left, top, right - left, bottom - top);
}

bool ItemGOSignal::isSelectable(float x, float y)
{
    if (this->_endPos.x() == 0 && this->_endPos.y() == 0)
    {
        return false;
    }
    x -= this->pos().x();
    y -= this->pos().y();
    qreal length = qFabs((1.0 * this->_endPos.y() * x - this->_endPos.x() * y) / qSqrt(this->_endPos.x() * this->_endPos.x() + this->_endPos.y() * this->_endPos.y()));
    return length < 5;
}

bool ItemGOSignal::isSelectable(float x, float y, float width, float height)
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
    float thisLeft, thisRight, thisTop, thisBottom;
    if (this->_endPos.x() >= 0)
    {
        thisLeft = this->pos().x();
        thisRight = this->pos().x() + this->_endPos.x();
    }
    else
    {
        thisLeft = this->pos().x() + this->_endPos.x();
        thisRight = this->pos().x();
    }
    if (this->_endPos.y() >= 0)
    {
        thisTop = this->pos().y();
        thisBottom = this->pos().y() + this->_endPos.y();
    }
    else
    {
        thisTop = this->pos().y() + this->_endPos.y();
        thisBottom = this->pos().y();
    }
    return left < thisLeft &&
            right > thisRight &&
            top < thisTop &&
            bottom > thisBottom;
}

/**
 * Get the start structure.
 * @return Start structure.
 */
ItemGOSignal::SignalConnection* ItemGOSignal::start()
{
    return this->_start;
}

/**
 * Get the end structure.
 * @return End structure.
 */
ItemGOSignal::SignalConnection* ItemGOSignal::end()
{
    return this->_end;
}

/**
 * Set the end position.
 * @param x X position.
 * @param y Y position.
 */
void ItemGOSignal::setEndPosition(int x, int y)
{
    this->_endPos.setX(x);
    this->_endPos.setY(y);
    this->update();
    this->prepareGeometryChange();
}

/**
 * Set the end position.
 * @param pos End position.
 */
void ItemGOSignal::setEndPosition(QPointF pos)
{
    this->setEndPosition((int)pos.x(), (int)pos.y());
}

/**
 * Paint a line.
 * @param painter The painter.
 * @param item The option.
 * @param widget The widget.
 */
void ItemGOSignal::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item);
    Q_UNUSED(widget);
    painter->setPen(Qt::SolidLine);
    painter->setPen(this->_color);
    painter->setBrush(this->_color);
    QFont font;
    font.setPixelSize(16);
    painter->setFont(font);
    painter->drawLine(QPointF(0, 0), this->_endPos);
    painter->drawText((this->_endPos.x() >> 1) + 5, (this->_endPos.y() >> 1), QString("%1").arg(this->model()->id()));
}

/**
 * Update the position.
 */
void ItemGOSignal::updatePosition()
{
    if (this->start()->op != 0L && this->end()->op != 0L)
    {
        switch (this->start()->type)
        {
        case DefinationGOType::GO_OPERATOR_INPUT:
            this->setPos(this->start()->op->pos() + this->start()->op->getInputPosition(this->start()->index));
            break;
        case DefinationGOType::GO_OPERATOR_SUBINPUT:
            this->setPos(this->start()->op->pos() + this->start()->op->getSubInputPosition(this->start()->index));
            break;
        case DefinationGOType::GO_OPERATOR_OUTPUT:
            this->setPos(this->start()->op->pos() + this->start()->op->getOutputPosition(this->start()->index));
            break;
        }
        switch (this->end()->type)
        {
        case DefinationGOType::GO_OPERATOR_INPUT:
            this->setEndPosition(this->end()->op->pos() + this->end()->op->getInputPosition(this->end()->index) - this->pos());
            break;
        case DefinationGOType::GO_OPERATOR_SUBINPUT:
            this->setEndPosition(this->end()->op->pos() + this->end()->op->getSubInputPosition(this->end()->index) - this->pos());
            break;
        case DefinationGOType::GO_OPERATOR_OUTPUT:
            this->setEndPosition(this->end()->op->pos() + this->end()->op->getOutputPosition(this->end()->index) - this->pos());
            break;
        }
        this->update();
        this->prepareGeometryChange();
    }
}

/**
 * Remove the connection of the signal.
 */
void ItemGOSignal::removeConnection()
{
    if (this->_start->op != 0L)
    {
        this->start()->op->removeSignal(this, this->start()->type, this->start()->index);
    }
    if (this->_end->op != 0L)
    {
        this->end()->op->removeSignal(this, this->end()->type, this->end()->index);
    }
}

void ItemGOSignal::save(QDomDocument &document, QDomElement &root)
{
    if (this->_start->op != 0L && this->_end->op != 0L)
    {
        QDomElement signalRoot = document.createElement("signal");
        signalRoot.setAttribute("id", this->model()->id());
        root.appendChild(signalRoot);
        QDomElement element = document.createElement("io");
        element.setAttribute("id", this->start()->op->model()->id());
        element.setAttribute("type", this->start()->type);
        element.setAttribute("index", this->start()->index);
        signalRoot.appendChild(element);
        element = document.createElement("io");
        element.setAttribute("id", this->end()->op->model()->id());
        element.setAttribute("type", this->end()->type);
        element.setAttribute("index", this->end()->index);
        signalRoot.appendChild(element);
    }
}

bool ItemGOSignal::tryOpen(QDomElement &root)
{
    if (root.tagName() != "signal")
    {
        return false;
    }
    this->model()->setId(root.attribute("id").toInt());
    QDomElement element = root.firstChildElement();
    this->_start->id = element.attribute("id").toInt();
    this->_start->type = element.attribute("type").toInt();
    this->_start->index = element.attribute("index").toInt();
    element = element.nextSiblingElement();
    this->_end->id = element.attribute("id").toInt();
    this->_end->type = element.attribute("type").toInt();
    this->_end->index = element.attribute("index").toInt();
    return true;
}

GOSignal *ItemGOSignal::model()
{
    return this->_model;
}
