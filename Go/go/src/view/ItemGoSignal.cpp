#include <QtAlgorithms>
#include <algorithm>
#include "ItemGoSignal.h"
#include "ItemGoOperator.h"
#include "GoOperator.h"
#include "DefinationGoType.h"
#include "DefinationEditorSelectionType.h"
#include "GoSignalFactory.h"
#include "GoOutput.h"
using namespace std;

ItemGoSignal::ItemGoSignal(QGraphicsItem *parent) : ItemDrawable(parent)
{
    this->_start = new SignalConnection();
    this->_end = new SignalConnection();
    this->_start->op = nullptr;
    this->_end->op = nullptr;
    this->setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL);
    this->_model = GoSignalFactory::produce();
    this->setCornerProportion(0.5f);
    this->setIsBrokenLine(true);
}

ItemGoSignal::~ItemGoSignal()
{
    delete this->_model;
    delete this->_start;
    delete this->_end;
}

QRectF ItemGoSignal::boundingRect() const
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

bool ItemGoSignal::isSelectable(float x, float y)
{
    if (this->isStraightLine())
    {
        x -= this->pos().x();
        y -= this->pos().y();
        qreal length = qFabs((1.0 * this->_endPos.y() * x - this->_endPos.x() * y) / qSqrt(this->_endPos.x() * this->_endPos.x() + this->_endPos.y() * this->_endPos.y()));
        return length < 5.0;
    }
    x -= this->pos().x();
    y -= this->pos().y();
    qreal corner = this->_endPos.x() * cornerProportion();
    if (x > min(0.0, corner) && x < max(0.0, corner))
    {
        return fabs(y - 0.0) < 5.0;
    }
    if (x > min(corner, this->_endPos.x()) && x < max(corner, this->_endPos.x()))
    {
        return fabs(y - this->_endPos.y()) < 5.0;
    }
    if (y > min(0.0, this->_endPos.y()) && y < max(0.0, this->_endPos.y()))
    {
        return fabs(x - corner) < 5.0;
    }
    return false;
}

bool ItemGoSignal::isCornerLineSelectable(float x, float y)
{
    if (this->isStraightLine())
    {
        return false;
    }
    x -= this->pos().x();
    y -= this->pos().y();
    qreal corner = this->_endPos.x() * cornerProportion();
    if (y > min(0.0, this->_endPos.y()))
    {
        if (y < max(0.0, this->_endPos.y()))
        {
            return fabs(x - corner) < 5.0;
        }
    }
    return false;
}

bool ItemGoSignal::isSelectable(float x, float y, float width, float height)
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

ItemGoSignal::SignalConnection* ItemGoSignal::start()
{
    return this->_start;
}

ItemGoSignal::SignalConnection* ItemGoSignal::end()
{
    return this->_end;
}

QPointF ItemGoSignal::endPos() const
{
    return this->_endPos;
}

void ItemGoSignal::setEndPosition(int x, int y)
{
    this->_endPos.setX(x);
    this->_endPos.setY(y);
    this->update();
    this->prepareGeometryChange();
}

bool ItemGoSignal::isStraightLine() const
{
    return this->_isStraightLine;
}

bool ItemGoSignal::isBrokenLine() const
{
    return !this->_isStraightLine;
}

void ItemGoSignal::setIsStraightLine(const bool value)
{
    this->_isStraightLine = value;
}

void ItemGoSignal::setIsBrokenLine(const bool value)
{
    this->_isStraightLine = !value;
}

float ItemGoSignal::cornerProportion() const
{
    return this->_cornerProportion;
}

void ItemGoSignal::setCornerProportion(const float value)
{
    if (value > 1.0f)
    {
        this->_cornerProportion = 1.0f;
    }
    else if (value < 0.0f)
    {
        this->_cornerProportion = 0.0f;
    }
    else
    {
        this->_cornerProportion = value;
    }
}

void ItemGoSignal::setEndPosition(QPointF pos)
{
    this->setEndPosition((int)pos.x(), (int)pos.y());
}

void ItemGoSignal::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item);
    Q_UNUSED(widget);
    if (this->model()->isGlobalFeedback())
    {
        painter->setOpacity(0.5);
    }
    painter->setPen(Qt::SolidLine);
    painter->setPen(this->_color);
    painter->setBrush(this->_color);
    QFont font;
    font.setPixelSize(16);
    painter->setFont(font);
    QString idName = QString("%1").arg(this->model()->id());
    if (this->model()->isGlobalFeedback())
    {
        idName += "'";
    }
    if (this->start()->op != nullptr)
    {
        if (this->start()->op->model()->output()->number() > 1)
        {
            idName += QString(" (%1)").arg(this->start()->index + 1);
        }
    }
    if (this->isStraightLine())
    {
        painter->drawLine(QPointF(0, 0), this->endPos());
        painter->drawText(this->endPos().x() * 0.5 - 10,
                          this->endPos().y() * 0.5 + 10,
                          idName);
    }
    else
    {
        float corner = this->_endPos.x() * cornerProportion();
        painter->drawLine(QPointF(0, 0), QPointF(corner, 0));
        painter->drawLine(QPointF(corner, 0), QPointF(corner, this->_endPos.y()));
        painter->drawLine(QPointF(corner, this->_endPos.y()), this->_endPos);
        painter->drawText(corner + 5,
                          this->_endPos.y() * 0.5 - 5,
                          idName);
    }
    if (this->model()->isGlobalFeedback())
    {
        painter->setOpacity(1.0);
    }
}

void ItemGoSignal::updatePosition()
{
    if (this->start()->op != nullptr && this->end()->op != nullptr)
    {
        switch (this->start()->type)
        {
        case DefinationGoType::GO_OPERATOR_INPUT:
            this->setPos(this->start()->op->pos() + this->start()->op->getInputPosition(this->start()->index));
            break;
        case DefinationGoType::GO_OPERATOR_SUBINPUT:
            this->setPos(this->start()->op->pos() + this->start()->op->getSubInputPosition(this->start()->index));
            break;
        case DefinationGoType::GO_OPERATOR_OUTPUT:
            this->setPos(this->start()->op->pos() + this->start()->op->getOutputPosition(this->start()->index));
            break;
        }
        switch (this->end()->type)
        {
        case DefinationGoType::GO_OPERATOR_INPUT:
            this->setEndPosition(this->end()->op->pos() + this->end()->op->getInputPosition(this->end()->index) - this->pos());
            break;
        case DefinationGoType::GO_OPERATOR_SUBINPUT:
            this->setEndPosition(this->end()->op->pos() + this->end()->op->getSubInputPosition(this->end()->index) - this->pos());
            break;
        case DefinationGoType::GO_OPERATOR_OUTPUT:
            this->setEndPosition(this->end()->op->pos() + this->end()->op->getOutputPosition(this->end()->index) - this->pos());
            break;
        }
        this->update();
        this->prepareGeometryChange();
    }
}

void ItemGoSignal::removeConnection()
{
    if (this->_start->op != nullptr)
    {
        this->start()->op->removeSignal(this, this->start()->type, this->start()->index);
    }
    if (this->_end->op != nullptr)
    {
        this->end()->op->removeSignal(this, this->end()->type, this->end()->index);
    }
}

ItemGoSignal* ItemGoSignal::copy() const
{
    ItemGoSignal* signal = new ItemGoSignal();
    signal->_start->id = this->_start->id;
    signal->_start->type = this->_start->type;
    signal->_start->index = this->_start->index;
    signal->_end->id = this->_end->id;
    signal->_end->type = this->_end->type;
    signal->_end->index = this->_end->index;
    signal->_isStraightLine = this->_isStraightLine;
    signal->_cornerProportion = this->_cornerProportion;
    signal->model()->setId(this->model()->id());
    signal->model()->setIsGlobalFeedback(this->model()->isGlobalFeedback());
    return signal;
}

void ItemGoSignal::save(QDomDocument &document, QDomElement &root)
{
    if (this->_start->op != nullptr && this->_end->op != nullptr)
    {
        QDomElement signalRoot = document.createElement("signal");
        signalRoot.setAttribute("id", this->model()->id());
        signalRoot.setAttribute("corner", this->cornerProportion());
        signalRoot.setAttribute("straight", this->isStraightLine());
        signalRoot.setAttribute("global_feedback", this->model()->isGlobalFeedback());
        root.appendChild(signalRoot);
        QDomElement element = document.createElement("io");
        element.setAttribute("id", this->start()->op->model()->realID());
        element.setAttribute("type", this->start()->type);
        element.setAttribute("index", this->start()->index);
        signalRoot.appendChild(element);
        element = document.createElement("io");
        element.setAttribute("id", this->end()->op->model()->realID());
        element.setAttribute("type", this->end()->type);
        element.setAttribute("index", this->end()->index);
        signalRoot.appendChild(element);
    }
}

bool ItemGoSignal::tryOpen(QDomElement &root)
{
    if (root.tagName() != "signal")
    {
        return false;
    }
    this->model()->setId(root.attribute("id").toInt());
    this->setCornerProportion(root.attribute("corner").toFloat());
    this->setIsStraightLine(root.attribute("straight").toInt());
    this->model()->setIsGlobalFeedback(root.attribute("global_feedback", "0").toInt());
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

GoSignal *ItemGoSignal::model() const
{
    return this->_model;
}
