#ifndef ITEMGOMARKOVCOMMONCAUSE_H
#define ITEMGOMARKOVCOMMONCAUSE_H
#include "ItemMoveable.h"

class ItemGoMarkovOperator;
class GoMarkovOperator;
class GoMarkovCommonCause;

class ItemGoMarkovCommonCause : public ItemMoveable
{
public:
    ItemGoMarkovCommonCause(QGraphicsItem *parent = 0);
    virtual ~ItemGoMarkovCommonCause();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    GoMarkovCommonCause *model();
    void bindOperators(QList<ItemGoMarkovOperator*> &operatorList);
    void updateBoundary();
    QVector<ItemGoMarkovOperator*>* operatorItems() const;
    ItemGoMarkovCommonCause* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    QVector<ItemGoMarkovOperator*> *_operatorItems;
    QPointF _end;
    GoMarkovCommonCause *_model;
};

#endif // ITEMGOMARKOVCOMMONCAUSE_H
