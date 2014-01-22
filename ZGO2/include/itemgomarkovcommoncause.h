#ifndef ITEMGOMARKOVCOMMONCAUSE_H
#define ITEMGOMARKOVCOMMONCAUSE_H
#include "itemmoveable.h"

class ItemGOMarkovOperator;
class GOMarkovOperator;
class GOMarkovCommonCause;

class ItemGOMarkovCommonCause : public ItemMoveable
{
public:
    ItemGOMarkovCommonCause(QGraphicsItem *parent = 0);
    virtual ~ItemGOMarkovCommonCause();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    GOMarkovCommonCause *model();
    void bindOperators(QList<ItemGOMarkovOperator*> &operatorList);
    void updateBoundary();
    QVector<ItemGOMarkovOperator*>* operatorItems() const;
    ItemGOMarkovCommonCause* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    QVector<ItemGOMarkovOperator*> *_operatorItems;
    QPointF _end;
    GOMarkovCommonCause *_model;
};

#endif // ITEMGOMARKOVCOMMONCAUSE_H
