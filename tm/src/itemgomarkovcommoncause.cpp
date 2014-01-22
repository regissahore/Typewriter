#include "itemgomarkovcommoncause.h"
#include "gomarkovcommoncause.h"
#include "itemgomarkovoperator.h"
#include "gomarkovoperator.h"
#include "definationeditorselectiontype.h"

ItemGOMarkovCommonCause::ItemGOMarkovCommonCause(QGraphicsItem *parent) : ItemMoveable(parent)
{
    this->TypedItem::setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE);
    this->_model = new GOMarkovCommonCause();
    this->_operatorItems = new QVector<ItemGOMarkovOperator*>();
}

ItemGOMarkovCommonCause::~ItemGOMarkovCommonCause()
{
    delete this->_model;
    this->_operatorItems->clear();
    delete this->_operatorItems;
}

QRectF ItemGOMarkovCommonCause::boundingRect() const
{
    return QRectF(0, 0, this->_end.x(), this->_end.y());
}

void ItemGOMarkovCommonCause::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::NoBrush);
    QFont font;
    font.setPixelSize(16);
    painter->setFont(font);
    painter->drawRoundedRect(0, 0, this->_end.x(), this->_end.y(), 10, 10);
    painter->drawText(QRectF(5, 5, 100, 100), Qt::AlignTop | Qt::AlignLeft, "C");
}

GOMarkovCommonCause *ItemGOMarkovCommonCause::model()
{
    return this->_model;
}

void ItemGOMarkovCommonCause::bindOperators(QList<ItemGOMarkovOperator*> &operatorList)
{
    for (int i = 0; i < operatorList.size(); ++i)
    {
        for (int j = 0; j < this->model()->idList()->size(); ++j)
        {
            if (operatorList[i]->model()->realID() == this->model()->idList()->at(j))
            {
                this->_operatorItems->push_back(operatorList[i]);
                this->model()->operators()->push_back((GOMarkovOperator*)operatorList[i]->model());
                operatorList[i]->setFatherCommonCause(this);
                break;
            }
        }
    }
    this->updateBoundary();
}

void ItemGOMarkovCommonCause::updateBoundary()
{
    qreal left = 2000000000;
    qreal right = -2000000000;
    qreal top = 2000000000;
    qreal bottom = -2000000000;
    for (int i = 0; i < this->_operatorItems->size(); ++i)
    {
        if (this->_operatorItems->at(i)->x() - 30 < left)
        {
            left = this->_operatorItems->at(i)->x() - 30;
        }
        if (this->_operatorItems->at(i)->x() + 30 > right)
        {
            right = this->_operatorItems->at(i)->x() + 30;
        }
        if (this->_operatorItems->at(i)->y() - 30 < top)
        {
            top = this->_operatorItems->at(i)->y() - 30;
        }
        if (this->_operatorItems->at(i)->y() + 30 > bottom)
        {
            bottom = this->_operatorItems->at(i)->y() + 30;
        }
    }
    qreal width = right - left;
    qreal height = bottom - top;
    this->setPos(left, top);
    this->_end.setX(width);
    this->_end.setY(height);
    this->prepareGeometryChange();
}

QVector<ItemGOMarkovOperator*>* ItemGOMarkovCommonCause::operatorItems() const
{
    return this->_operatorItems;
}

ItemGOMarkovCommonCause* ItemGOMarkovCommonCause::copy()
{
    ItemGOMarkovCommonCause *common = new ItemGOMarkovCommonCause();
    common->_model = this->model()->copy();
    for (int i = 0; i < this->_operatorItems->size(); ++i)
    {
        common->_operatorItems->push_back(0L);
    }
    return common;
}

void ItemGOMarkovCommonCause::save(QDomDocument &document, QDomElement &root)
{
    this->model()->save(document, root);
}

bool ItemGOMarkovCommonCause::tryOpen(QDomElement &root)
{
    return this->model()->tryOpen(root);
}
