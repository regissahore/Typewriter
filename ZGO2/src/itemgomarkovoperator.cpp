#include "itemgomarkovoperator.h"
#include "definationeditorselectiontype.h"
#include "gomarkovoperatorfactory.h"
#include "gomarkovoperator.h"
#include "itemgomarkovequivalent.h"
#include "itemgomarkovcommoncause.h"
#include "gomarkovoperator9a.h"
#include "gomarkovoperator13.h"
#include "goinput.h"
#include "gooutput.h"

ItemGOMarkovOperator::ItemGOMarkovOperator(QGraphicsItem *parent) : ItemGOOperator(parent)
{
    this->TypedItem::setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR);
    this->_fatherEquivalent = 0L;
    this->_fatherCommonCause = 0L;
}

ItemGOMarkovEquivalent* ItemGOMarkovOperator::fatherEquivalent() const
{
    return this->_fatherEquivalent;
}

ItemGOMarkovEquivalent* ItemGOMarkovOperator::rootEquivalent() const
{
    if (this->fatherEquivalent() != 0L)
    {
        ItemGOMarkovEquivalent *eq = this->fatherEquivalent();
        while (eq->fatherEquivalent() != 0L)
        {
            eq = eq->fatherEquivalent();
        }
        return eq;
    }
    return 0L;
}

void ItemGOMarkovOperator::setFatherEquivalent(ItemGOMarkovEquivalent* equivalent)
{
    this->_fatherEquivalent = equivalent;
}

ItemGOMarkovCommonCause* ItemGOMarkovOperator::fatherCommonCause() const
{
    return this->_fatherCommonCause;
}

void ItemGOMarkovOperator::setFatherCommonCause(ItemGOMarkovCommonCause* commonCause)
{
    this->_fatherCommonCause = commonCause;
}

void ItemGOMarkovOperator::move(QGraphicsSceneMouseEvent *event)
{
    this->ItemGOOperator::move(event);
    if (this->fatherEquivalent() != 0L)
    {
        this->fatherEquivalent()->updateBoundary();
    }
    if (this->fatherCommonCause() != 0L)
    {
        this->fatherCommonCause()->updateBoundary();
    }
}

void ItemGOMarkovOperator::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item);
    Q_UNUSED(widget);
    painter->setPen(Qt::SolidLine);
    painter->setPen(this->_color);
    painter->setBrush(Qt::NoBrush);
    QFont font;
    font.setPixelSize(16);
    painter->setFont(font);
    QString typeName = GOMarkovOperatorFactory::typeName(this->model()->type());
    if (this->isSource())
    {
        painter->drawText(QRectF(-100, -100, 200, 200), Qt::AlignHCenter | Qt::AlignVCenter, QString(typeName + "-%1").arg(this->model()->id()));
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
                          QString(typeName + "-%1").arg(this->model()->id()));
        painter->drawEllipse(QPoint(0, 0), 25, 25);
    }
    painter->setPen(Qt::gray);
    for (int i = 0; i < this->model()->input()->number(); ++i)
    {
        QPoint pos = this->getInputPosition(i);
        QString text = "S";
        if (this->model()->input()->number() + this->model()->subInput()->number() != 1)
        {
            text += QString("%1").arg(i + 1);
        }
        if (pos.x() < 0)
        {
            painter->drawText(QRectF(pos.x() + 10, pos.y() - 20, 100, 100),
                              Qt::AlignLeft | Qt::AlignTop,
                              text);
        }
        else
        {
            painter->drawText(QRectF(pos.x() - 110, pos.y() - 20, 100, 100),
                              Qt::AlignRight | Qt::AlignTop,
                              text);
        }
    }
    for (int i = 0; i < this->model()->subInput()->number(); ++i)
    {
        QPoint pos = this->getSubInputPosition(i);
        QString text = "S";
        if (this->model()->input()->number() + this->model()->subInput()->number() != 1)
        {
            text += QString("%1").arg(this->model()->input()->number() + i + 1);
        }
        if (pos.y() < 0)
        {
            painter->drawText(QRectF(pos.x() - 20, pos.y() + 10, 100, 100),
                              Qt::AlignLeft | Qt::AlignTop,
                              text);
        }
        else
        {
            painter->drawText(QRectF(pos.x() - 20, pos.y() - 110, 100, 100),
                              Qt::AlignLeft | Qt::AlignBottom,
                              text);
        }
    }
    for (int i = 0; i < this->model()->output()->number(); ++i)
    {
        QPoint pos = this->getOutputPosition(i);
        QString text = "R";
        if (this->model()->output()->number() != 1)
        {
            text += QString("%1").arg(i + 1);
        }
        if (pos.x() < 0)
        {
            painter->drawText(QRectF(pos.x() + 10, pos.y() - 20, 100, 100),
                              Qt::AlignLeft | Qt::AlignTop,
                              text);
        }
        else
        {
            painter->drawText(QRectF(pos.x() - 110, pos.y() - 20, 100, 100),
                              Qt::AlignRight | Qt::AlignTop,
                              text);
        }
    }
    painter->setPen(this->_color);
}

void ItemGOMarkovOperator::setModelType(const int type)
{
    this->_model = GOMarkovOperatorFactory::produce(type);
    this->setModel(this->_model);
}

ItemGOMarkovOperator* ItemGOMarkovOperator::copy()
{
    ItemGOMarkovOperator* op = new ItemGOMarkovOperator();
    op->setType(this->TypedItem::type());
    op->setX(this->x() + 100);
    op->setY(this->y() + 100);
    op->setIsHorizonFlip(this->isHorizonFlip());
    op->setIsVerticalFlip(this->isVerticalFlip());
    op->setModel(((GOMarkovOperator*)this->model())->copy());
    return op;
}

bool ItemGOMarkovOperator::tryOpen(QDomElement &root)
{
    if (root.tagName() != "operator")
    {
        return false;
    }
    this->setX(root.attribute("x", "0").toFloat());
    this->setY(root.attribute("y", "0").toFloat());
    this->setIsHorizonFlip(root.attribute("horizon").toInt());
    this->setIsVerticalFlip(root.attribute("vertical").toInt());
    int type = root.attribute("type").toInt();
    QDomElement element = root.firstChildElement();
    GOMarkovOperator *model = GOMarkovOperatorFactory::produce(type);
    if (!model->tryOpen(element))
    {
        return false;
    }
    this->setModel(model);
    return true;
}

bool ItemGOMarkovOperator::isSource() const
{
    return this->model()->type() == GOMarkovOperatorFactory::Operator_Type_4 ||
            this->model()->type() == GOMarkovOperatorFactory::Operator_Type_5;
}
