#include <QObject>
#include "ItemGoMarkovCommonCause2.h"
#include "GoMarkovCommonCause.h"
#include "ItemGoMarkovOperator.h"
#include "GoMarkovOperator.h"
#include "DefinationEditorSelectionType.h"
#include "GoMarkovOperatorFactory.h"

ItemGoMarkovCommonCause2::ItemGoMarkovCommonCause2(QGraphicsItem *parent) : ItemMoveable(parent)
{
    this->TypedItem::setType(DefinationEditorSelectionType::EDITOR_SELECTION_Go_MARKOV_COMMON_CAUSE_2);
    this->_model = new GoMarkovCommonCause();
    this->_operatorItems = new QVector<ItemGoMarkovOperator*>();
    this->_end.setX(200);
    this->_end.setY(300);
}

ItemGoMarkovCommonCause2::~ItemGoMarkovCommonCause2()
{
    delete this->_model;
    this->_operatorItems->clear();
    delete this->_operatorItems;
}

QRectF ItemGoMarkovCommonCause2::boundingRect() const
{
    return QRectF(0, 0, this->_end.x(), this->_end.y());
}

void ItemGoMarkovCommonCause2::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::NoBrush);
    QFont font;
    font.setPixelSize(16);
    painter->setFont(font);
    painter->drawRoundedRect(0, 0, this->_end.x(), this->_end.y(), 10, 10);
    painter->drawText(QRectF(5, 5, 200, 100), Qt::AlignTop | Qt::AlignLeft, "C");
    painter->drawText(QRectF(5, 25, 200, 100), Qt::AlignTop | Qt::AlignLeft, QObject::tr("Total Breakdown: %1").arg(this->model()->breakdownTotal()));
    painter->drawText(QRectF(5, 45, 200, 100), Qt::AlignTop | Qt::AlignLeft, QObject::tr("Individual Breakdown: %1").arg(this->model()->breakdownIndividual()));
    painter->drawText(QRectF(5, 65, 200, 100), Qt::AlignTop | Qt::AlignLeft, QObject::tr("Common Breakdown: %1").arg(this->model()->breakdownCommon()));
    painter->drawText(QRectF(5, 85, 200, 100), Qt::AlignTop | Qt::AlignLeft, QObject::tr("Belta: %1").arg(this->model()->belta()));
    painter->drawText(QRectF(5, 105, 200, 100), Qt::AlignTop | Qt::AlignLeft, QObject::tr("Gamma C: %1").arg(this->model()->gammaC()));
    painter->drawText(QRectF(5, 125, 200, 100), Qt::AlignTop | Qt::AlignLeft, QObject::tr("Operators: "));
    int y = 145;
    for (int i = 0; i < this->_operatorItems->size(); ++i)
    {
        painter->drawText(QRectF(5, y, 200, 100), Qt::AlignTop | Qt::AlignLeft, GoMarkovOperatorFactory::typeName(this->_operatorItems->at(i)->model()->TypedItem::type()) + QString(" - %1").arg(this->_operatorItems->at(i)->model()->id()));
        y += 20;
    }
}

GoMarkovCommonCause *ItemGoMarkovCommonCause2::model()
{
    return this->_model;
}

void ItemGoMarkovCommonCause2::bindOperators(QList<ItemGoMarkovOperator*> &operatorList)
{
    for (int i = 0; i < operatorList.size(); ++i)
    {
        for (int j = 0; j < this->model()->idList()->size(); ++j)
        {
            if (operatorList[i]->model()->realID() == this->model()->idList()->at(j))
            {
                this->_operatorItems->push_back(operatorList[i]);
                this->model()->operators()->push_back((GoMarkovOperator*)operatorList[i]->model());
                operatorList[i]->setFatherCommonCause2(this);
                break;
            }
        }
    }
    this->updateBoundary();
}

void ItemGoMarkovCommonCause2::updateBoundary()
{
    this->_end.setY(145 + 20 * this->_operatorItems->size() + 5);
}

QVector<ItemGoMarkovOperator*>* ItemGoMarkovCommonCause2::operatorItems() const
{
    return this->_operatorItems;
}

ItemGoMarkovCommonCause2* ItemGoMarkovCommonCause2::copy()
{
    ItemGoMarkovCommonCause2 *common = new ItemGoMarkovCommonCause2();
    common->_model = this->model()->copy();
    for (int i = 0; i < this->_operatorItems->size(); ++i)
    {
        common->_operatorItems->push_back(0L);
    }
    common->setX(this->scenePos().x() + 100);
    common->setY(this->scenePos().y() + 100);
    return common;
}

void ItemGoMarkovCommonCause2::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("commoncause");
    element.setAttribute("x", this->scenePos().x());
    element.setAttribute("y", this->scenePos().y());
    root.appendChild(element);
    this->model()->save(document, element);
}

bool ItemGoMarkovCommonCause2::tryOpen(QDomElement &root)
{
    this->setX(root.attribute("x").toInt());
    this->setY(root.attribute("y").toInt());
    QDomElement element = root.firstChildElement();
    return this->model()->tryOpen(element);
}
