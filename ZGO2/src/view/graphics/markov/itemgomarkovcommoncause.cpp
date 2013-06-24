#include "itemgomarkovcommoncause.h"
#include "gomarkovcommoncause.h"
#include "itemgomarkovoperator.h"
#include "gomarkovoperator.h"

ItemGOMarkovCommonCause::ItemGOMarkovCommonCause(QGraphicsItem *parent) : ItemMoveable(parent), IdentifiedItem()
{
    this->_model = new GOMarkovCommonCause();
}

ItemGOMarkovCommonCause::~ItemGOMarkovCommonCause()
{
    delete this->_model;
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
    painter->drawText(QRectF(5, 5, 100, 100), Qt::AlignTop | Qt::AlignLeft, QString("%1").arg(this->id()));
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
            if (operatorList[i]->model()->id() == this->model()->idList()->at(j))
            {
                this->_operatorItems->push_back(operatorList[i]);
                this->model()->operators()->push_back(operatorList[i]->model());
                break;
            }
        }
    }
}
