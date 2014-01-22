#ifndef ITEMGOMARKOVCOMMONCAUSE2_H
#define ITEMGOMARKOVCOMMONCAUSE2_H
#include "itemmoveable.h"

class GOMarkovCommonCause;
class ItemGOMarkovOperator;

class ItemGOMarkovCommonCause2 : public ItemMoveable
{
public:
    ItemGOMarkovCommonCause2(QGraphicsItem *parent = 0L);
    virtual ~ItemGOMarkovCommonCause2();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    GOMarkovCommonCause *model();
    void bindOperators(QList<ItemGOMarkovOperator*> &operatorList);
    void updateBoundary();
    QVector<ItemGOMarkovOperator*>* operatorItems() const;
    ItemGOMarkovCommonCause2* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    QVector<ItemGOMarkovOperator*> *_operatorItems;
    QPointF _end;
    GOMarkovCommonCause *_model;
};

#endif // ITEMGOMARKOVCOMMONCAUSE2_H
