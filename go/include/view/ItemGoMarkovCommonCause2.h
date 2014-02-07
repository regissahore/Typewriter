#ifndef ITEMGOMARKOVCOMMONCAUSE2_H
#define ITEMGOMARKOVCOMMONCAUSE2_H
#include "ItemMoveable.h"

class GoMarkovCommonCause;
class ItemGoMarkovOperator;

class ItemGoMarkovCommonCause2 : public ItemMoveable
{
public:
    ItemGoMarkovCommonCause2(QGraphicsItem *parent = nullptr);
    virtual ~ItemGoMarkovCommonCause2();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    GoMarkovCommonCause *model();
    void bindOperators(QList<ItemGoMarkovOperator*> &operatorList);
    void updateBoundary();
    QVector<ItemGoMarkovOperator*>* operatorItems() const;
    ItemGoMarkovCommonCause2* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    QVector<ItemGoMarkovOperator*> *_operatorItems;
    QPointF _end;
    GoMarkovCommonCause *_model;
};

#endif // ITEMGOMARKOVCOMMONCAUSE2_H
