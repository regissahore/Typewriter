#include "itemgomarkovcommoncause.h"


ItemGOMarkovCommonCause::ItemGOMarkovCommonCause(QGraphicsItem *parent) : ItemMoveable(parent), IdentifiedItem()
{
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
