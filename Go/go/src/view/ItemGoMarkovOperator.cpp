#include <QColor>
#include "ItemGoMarkovOperator.h"
#include "DefinationEditorSelectionType.h"
#include "GoMarkovOperatorFactory.h"
#include "GoMarkovOperator.h"
#include "ItemGoMarkovEquivalent.h"
#include "ItemGoMarkovCommonCause.h"
#include "GoMarkovOperator9a.h"
#include "GoMarkovOperator13.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "ItemArrow.h"
#include "ItemGoSignal.h"

ItemGoMarkovOperator::ItemGoMarkovOperator(QGraphicsItem *parent) : ItemGoOperator(parent)
{
    this->TypedItem::setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR);
    this->_fatherEquivalent = nullptr;
    this->_fatherCommonCause = nullptr;
}

ItemGoMarkovEquivalent* ItemGoMarkovOperator::fatherEquivalent() const
{
    return this->_fatherEquivalent;
}

ItemGoMarkovEquivalent* ItemGoMarkovOperator::rootEquivalent() const
{
    if (this->fatherEquivalent() != nullptr)
    {
        ItemGoMarkovEquivalent *eq = this->fatherEquivalent();
        while (eq->fatherEquivalent() != nullptr)
        {
            eq = eq->fatherEquivalent();
        }
        return eq;
    }
    return nullptr;
}

void ItemGoMarkovOperator::setFatherEquivalent(ItemGoMarkovEquivalent* equivalent)
{
    this->_fatherEquivalent = equivalent;
}

ItemGoMarkovCommonCause* ItemGoMarkovOperator::fatherCommonCause() const
{
    return this->_fatherCommonCause;
}

void ItemGoMarkovOperator::setFatherCommonCause(ItemGoMarkovCommonCause* commonCause)
{
    this->_fatherCommonCause = commonCause;
}

void ItemGoMarkovOperator::move(QGraphicsSceneMouseEvent *event)
{
    this->ItemGoOperator::move(event);
    if (this->fatherEquivalent() != nullptr)
    {
        this->fatherEquivalent()->updateBoundary();
    }
}

void ItemGoMarkovOperator::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(item);
    Q_UNUSED(widget);
    this->updateArrowColor();
    if (((GoMarkovOperator*)this->model())->isGlobalFeedback())
    {
        painter->setOpacity(0.5);
    }
    for (int i = 0; i < this->model()->output()->number(); ++i)
    {
        this->_outputArrows->at(i)->setVisible(this->isShowOutput()->at(i));
    }
    if (this->isDrawName())
    {
        QFont font;
        font.setPixelSize(16);
        painter->setFont(font);
        painter->drawText(-200, -230, 400, 200, Qt::AlignHCenter | Qt::AlignBottom, this->model()->name());
    }
    switch (this->model()->TypedItem::type())
    {
    case GoMarkovOperatorFactory::Operator_Type_9A1:
    case GoMarkovOperatorFactory::Operator_Type_9A2:
    case GoMarkovOperatorFactory::Operator_Type_9B1:
    case GoMarkovOperatorFactory::Operator_Type_9B2:
        this->paint9A(painter);
        break;
    case GoMarkovOperatorFactory::Operator_Type_22B:
        this->paint22B(painter);
        break;
    case GoMarkovOperatorFactory::Operator_Type_Split:
        this->paintSplit(painter);
        break;
    default:
        this->paint(painter);
        break;
    }
    if (this->isDrawParameter())
    {
        ((GoMarkovOperator*)this->model())->paintParameter(painter);
    }
    if (((GoMarkovOperator*)this->model())->isGlobalFeedback())
    {
        painter->setOpacity(1.0);
    }
}

void ItemGoMarkovOperator::paint(QPainter *painter)
{
    painter->setPen(Qt::SolidLine);
    painter->setPen(this->_color);
    painter->setBrush(Qt::NoBrush);
    QFont font;
    font.setPixelSize(16);
    painter->setFont(font);
    QString typeName = GoMarkovOperatorFactory::typeName(this->model()->type());
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
        if (this->isShowOutput()->at(i))
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
    }
    painter->setPen(this->_color);
}

void ItemGoMarkovOperator::paint9A(QPainter *painter)
{
    painter->setPen(Qt::SolidLine);
    painter->setPen(this->_color);
    painter->setBrush(Qt::NoBrush);
    QFont font;
    font.setPixelSize(16);
    painter->setFont(font);
    QString typeName = GoMarkovOperatorFactory::typeName(this->model()->type());
    painter->drawText(QRectF(-100, -100, 200, 200),
                      Qt::AlignHCenter | Qt::AlignVCenter,
                      QString(typeName + "-%1").arg(this->model()->id()));
    painter->drawEllipse(QPoint(0, 0), 25, 25);
    QPointF pos[6];
    pos[0].setX(40), pos[0].setY(0);
    pos[1].setX(40), pos[1].setY(-50);
    pos[2].setX(0), pos[2].setY(-50);
    pos[3].setX(0), pos[3].setY(-25);
    pos[4].setX(-4), pos[4].setY(-40);
    pos[5].setX(4), pos[5].setY(-40);
    if (this->isHorizonFlip())
    {
        for (int i = 0; i < 6; ++i)
        {
            pos[i].setX(-pos[i].x());
        }
    }
    if (this->isVerticalFlip())
    {
        for (int i = 0; i < 6; ++i)
        {
            pos[i].setY(-pos[i].y());
        }
    }
    for (int i = 0; i < 3; ++i)
    {
        painter->drawLine(pos[i], pos[i + 1]);
    }
    painter->setBrush(this->_color);
    painter->drawPolygon(pos + 3, 3);
    painter->setPen(Qt::gray);
    for (int i = 0; i < this->model()->input()->number(); ++i)
    {
        QPoint pos = this->getInputPosition(i);
        QString text = "S";
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
    for (int i = 0; i < this->model()->output()->number(); ++i)
    {
        QPoint pos = this->getOutputPosition(i);
        QString text = "R";
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

void ItemGoMarkovOperator::paint22B(QPainter *painter)
{
    painter->setPen(Qt::SolidLine);
    painter->setPen(this->_color);
    painter->setBrush(Qt::NoBrush);
    QFont font;
    font.setPixelSize(16);
    painter->setFont(font);
    QString typeName = GoMarkovOperatorFactory::typeName(this->model()->type());
    painter->drawText(QRectF(-100, -100, 200, 200),
                      Qt::AlignHCenter | Qt::AlignVCenter,
                      QString(typeName + "-%1").arg(this->model()->id()));
    painter->drawEllipse(QPoint(0, 0), 25, 25);
    painter->setPen(Qt::gray);
    for (int i = 0; i < this->model()->input()->number(); ++i)
    {
        QPoint pos = this->getInputPosition(i);
        QString text = "S";
        if (i == 0)
        {
            text += "1";
        }
        else if (i == 1)
        {
            text += "3";
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
        QString text = "S2";
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

void ItemGoMarkovOperator::paintSplit(QPainter *painter)
{
    painter->setPen(Qt::SolidLine);
    painter->setPen(this->_color);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::gray);
    for (int i = 0; i < this->model()->input()->number(); ++i)
    {
        QPoint pos = this->getInputPosition(i);
        QString text = "S";
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
    for (int i = 0; i < this->model()->output()->number(); ++i)
    {
        if (this->isShowOutput()->at(i))
        {
            QPoint pos = this->getOutputPosition(i);
            QString text = QString("R%1").arg(i + 1);
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
    }
    painter->setPen(this->_color);
    painter->setBrush(this->_color);
    int number = this->model()->output()->number();
    int y = - (number - 1) * 25;
    painter->drawLine(0, -y, 0, y);
    painter->drawEllipse(-5, -5, 10, 10);
}

void ItemGoMarkovOperator::setModelType(const int type)
{
    this->_model = GoMarkovOperatorFactory::produce(type);
    this->setModel(this->_model);
}

void ItemGoMarkovOperator::setModel(GoOperator *model)
{
    if (model->type() == GoMarkovOperatorFactory::Operator_Type_Split)
    {
        this->_model = model;
        this->_inputSignal->clear();
        this->_subInputSignal->clear();
        this->_outputSignal->clear();
        for (int i = 0; i < this->_inputArrows->size(); ++i)
        {
            this->_inputArrows->at(i)->setParentItem(nullptr);
            delete this->_inputArrows->at(i);
        }
        this->_inputArrows->clear();
        for (int i = 0; i < this->_subInputArrows->size(); ++i)
        {
            this->_subInputArrows->at(i)->setParentItem(nullptr);
            delete this->_subInputArrows->at(i);
        }
        this->_subInputArrows->clear();
        for (int i = 0; i < this->_outputArrows->size(); ++i)
        {
            this->_outputArrows->at(i)->setParentItem(nullptr);
            delete this->_outputArrows->at(i);
        }
        this->_outputArrows->clear();
        int number = this->model()->input()->number();
        double startY = - (number - 1) * 12.5;
        for (int i = 0; i < number; ++i)
        {
            ItemArrow *arrow = new ItemArrow(this);
            arrow->setIsShowArrow(false);
            arrow->setColor(QColor(Qt::darkRed));
            arrow->setPos(- 50, startY);
            double angle = atan2(-startY, 75);
            double dist = sqrt(startY * startY + 75 * 75);
            double x = (dist - 25.0) * cos(angle);
            double y = (dist - 25.0) * sin(angle);
            arrow->setEnd(QPoint(x, y));
            this->_inputArrows->push_back(arrow);
            startY += 25.0;
            this->_inputSignal->push_back(nullptr);
        }
        number = this->model()->output()->number();
        startY = - (number - 1) * 25;
        for (int i = 0; i < number; ++i)
        {
            ItemArrow *arrow = new ItemArrow(this);
            arrow->setPos(0, startY);
            arrow->setEnd(QPoint(50, 0));
            this->_outputArrows->push_back(arrow);
            startY += 50.0;
            this->_outputSignal->push_back(new QVector<ItemGoSignal*>());
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
    else if (model->type() == GoMarkovOperatorFactory::Operator_Type_19)
    {
        this->_model = model;
        this->_inputSignal->clear();
        this->_subInputSignal->clear();
        this->_outputSignal->clear();
        for (int i = 0; i < this->_inputArrows->size(); ++i)
        {
            this->_inputArrows->at(i)->setParentItem(nullptr);
            delete this->_inputArrows->at(i);
        }
        this->_inputArrows->clear();
        for (int i = 0; i < this->_subInputArrows->size(); ++i)
        {
            this->_subInputArrows->at(i)->setParentItem(nullptr);
            delete this->_subInputArrows->at(i);
        }
        this->_subInputArrows->clear();
        for (int i = 0; i < this->_outputArrows->size(); ++i)
        {
            this->_outputArrows->at(i)->setParentItem(nullptr);
            delete this->_outputArrows->at(i);
        }
        this->_outputArrows->clear();
        ItemArrow *arrow = new ItemArrow(this);
        arrow->setIsShowArrow(false);
        arrow->setColor(QColor(Qt::darkRed));
        arrow->setPos(-75, 0);
        arrow->setEnd(QPoint(50, 0));
        this->_inputArrows->push_back(arrow);
        this->_inputSignal->push_back(nullptr);
        arrow = new ItemArrow(this);
        arrow->setPos(25, 0);
        arrow->setEnd(QPoint(50, 0));
        this->_outputArrows->push_back(arrow);
        this->_outputSignal->push_back(new QVector<ItemGoSignal*>());
        arrow = new ItemArrow(this);
        arrow->setPos(0, 25);
        arrow->setEnd(QPoint(0, 50));
        this->_outputArrows->push_back(arrow);
        this->_outputSignal->push_back(new QVector<ItemGoSignal*>());
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
    else
    {
        this->ItemGoOperator::setModel(model);
    }
}

void ItemGoMarkovOperator::globalFeedbackExtend()
{
    if (((GoMarkovOperator*)this->model())->isGlobalFeedback())
    {
        for (int i = 0; i < this->input()->size(); ++i)
        {
            if (this->input()->at(i) != nullptr)
            {
                this->input()->at(i)->model()->setIsGlobalFeedback(true);
                this->input()->at(i)->update();
                ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->input()->at(i)->start()->op;
                GoMarkovOperator* op = (GoMarkovOperator*)item->model();
                if (!op->isGlobalFeedback())
                {
                    op->setIsGlobalFeedback(true);
                    item->globalFeedbackExtend();
                    item->update();
                }
            }
        }
        for (int i = 0; i < this->subInput()->size(); ++i)
        {
            if (this->subInput()->at(i) != nullptr)
            {
                this->subInput()->at(i)->model()->setIsGlobalFeedback(true);
                this->subInput()->at(i)->update();
                ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->subInput()->at(i)->start()->op;
                GoMarkovOperator* op = (GoMarkovOperator*)item->model();
                if (!op->isGlobalFeedback())
                {
                    op->setIsGlobalFeedback(true);
                    item->globalFeedbackExtend();
                    item->update();
                }
            }
        }
    }
}

QRectF ItemGoMarkovOperator::boundingRect() const
{
    if (this->model()->TypedItem::type() == GoMarkovOperatorFactory::Operator_Type_Split)
    {
        float height = (this->output()->size() - 1) * 100;
        if (this->isHorizonFlip())
        {
            return QRectF(-100, - height * 0.5f, 125, height);
        }
        return QRectF(-25, - height * 0.5f, 125, height);
    }
    return ItemGoOperator::boundingRect();
}

ItemGoMarkovOperator* ItemGoMarkovOperator::copy()
{
    ItemGoMarkovOperator* op = new ItemGoMarkovOperator();
    op->setType(this->TypedItem::type());
    op->setX(this->x() + 100);
    op->setY(this->y() + 100);
    op->setIsHorizonFlip(this->isHorizonFlip());
    op->setIsVerticalFlip(this->isVerticalFlip());
    op->setIsDrawParameter(this->isDrawParameter());
    op->setIsDrawName(this->isDrawName());
    op->setModel(((GoMarkovOperator*)this->model())->copy());
    for (int i = 0; i < this->model()->output()->number(); ++i)
    {
        (*op->isShowOutput())[i] = this->isShowOutput()->at(i);
    }
    return op;
}

bool ItemGoMarkovOperator::tryOpen(QDomElement &root)
{
    if (root.tagName() != "operator")
    {
        return false;
    }
    this->setX(root.attribute("x", "0").toFloat());
    this->setY(root.attribute("y", "0").toFloat());
    this->setIsHorizonFlip(root.attribute("horizon").toInt());
    this->setIsVerticalFlip(root.attribute("vertical").toInt());
    this->setIsDrawParameter(root.attribute("parameter", "0").toInt());
    this->setIsDrawName(root.attribute("name", "0").toInt());
    int type = root.attribute("type").toInt();
    QDomElement element = root.firstChildElement();
    GoMarkovOperator *model = GoMarkovOperatorFactory::produce(type);
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

bool ItemGoMarkovOperator::isSource() const
{
    return this->model()->type() == GoMarkovOperatorFactory::Operator_Type_4 ||
            this->model()->type() == GoMarkovOperatorFactory::Operator_Type_5;
}

void ItemGoMarkovOperator::updateArrowColor()
{
    if (((GoMarkovOperator*)this->model())->isGlobalFeedback())
    {
        for (int i = 0; i < this->_inputSignal->size(); ++i)
        {
            if (this->_inputSignal->at(i) == nullptr)
            {
                this->_inputArrows->at(i)->setColor(QColor(127, 0, 0, 127));
            }
            else
            {
                this->_inputArrows->at(i)->setColor(QColor(0, 0, 0, 127));
            }
        }
        for (int i = 0; i < this->_subInputSignal->size(); ++i)
        {
            if (this->_subInputSignal->at(i) == nullptr)
            {
                this->_subInputArrows->at(i)->setColor(QColor(127, 0, 0, 127));
            }
            else
            {
                this->_subInputArrows->at(i)->setColor(QColor(0, 0, 0, 127));
            }
        }
        for (int i = 0; i < this->_outputSignal->size(); ++i)
        {
            this->_outputArrows->at(i)->setColor(QColor(0, 0, 0, 127));
        }
    }
    else
    {
        for (int i = 0; i < this->_inputSignal->size(); ++i)
        {
            if (this->_inputSignal->at(i) == nullptr)
            {
                this->_inputArrows->at(i)->setColor(Qt::darkRed);
            }
            else
            {
                this->_inputArrows->at(i)->setColor(Qt::black);
            }
        }
        for (int i = 0; i < this->_subInputSignal->size(); ++i)
        {
            if (this->_subInputSignal->at(i) == nullptr)
            {
                this->_subInputArrows->at(i)->setColor(Qt::darkRed);
            }
            else
            {
                this->_subInputArrows->at(i)->setColor(Qt::black);
            }
        }
        for (int i = 0; i < this->_outputSignal->size(); ++i)
        {
            this->_outputArrows->at(i)->setColor(Qt::black);
        }
    }
    for (int i = 0; i < this->_outputSignal->size(); ++i)
    {
        if (this->_outputSignal->at(i)->size() == 0)
        {
            this->_outputArrows->at(i)->setIsShowArrow(true);
        }
        else
        {
            this->_outputArrows->at(i)->setIsShowArrow(false);
        }
    }
}
