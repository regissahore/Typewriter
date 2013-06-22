#ifndef ITEMGOMARKOVCOMMONCAUSE_H
#define ITEMGOMARKOVCOMMONCAUSE_H
/**
 * The common cause of Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "itemmoveable.h"
#include "identifieditem.h"

class ItemGOMarkovOperator;
class GOMarkovOperator;

class ItemGOMarkovCommonCause : public ItemMoveable, public IdentifiedItem
{
public:
    ItemGOMarkovCommonCause(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
private:
    QVector<ItemGOMarkovOperator*> *_operatorItems;
    QPointF _end;
};

#endif // ITEMGOMARKOVCOMMONCAUSE_H
