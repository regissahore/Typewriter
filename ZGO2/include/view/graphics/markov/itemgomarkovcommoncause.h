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
class GOMarkovCommonCause;

class ItemGOMarkovCommonCause : public ItemMoveable, public IdentifiedItem
{
public:
    ItemGOMarkovCommonCause(QGraphicsItem *parent = 0);
    virtual ~ItemGOMarkovCommonCause();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    GOMarkovCommonCause *model();
    void bindOperators(QList<ItemGOMarkovOperator*> &operatorList);

private:
    QVector<ItemGOMarkovOperator*> *_operatorItems;
    QPointF _end;
    GOMarkovCommonCause *_model;
};

#endif // ITEMGOMARKOVCOMMONCAUSE_H
