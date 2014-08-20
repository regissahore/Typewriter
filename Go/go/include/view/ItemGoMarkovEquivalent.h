#ifndef ITEMGOMARKOVEQUIVALENT_H
#define ITEMGOMARKOVEQUIVALENT_H
#include "stable.h"
#include "ItemMoveable.h"
#include "IdentifiedItem.h"
#include "DomItem.h"

class QGraphicsItem;
class ItemGoSignal;
class ItemGoMarkovOperator;
class GoMarkovOperator;
class GoMarkovEquivalent;

class ItemGoMarkovEquivalent : public ItemMoveable, public IdentifiedItem
{
public:
    ItemGoMarkovEquivalent(QGraphicsItem *parent = 0);
    ~ItemGoMarkovEquivalent();
    void setId(const int id);
    ItemGoMarkovEquivalent* fatherEquivalent() const;
    ItemGoMarkovEquivalent* rootEquivalent() const;
    void setFatherEquivalent(ItemGoMarkovEquivalent *equivalent);
    bool isSeriesEquivalentable(QList<QGraphicsItem*> items);
    bool isParallelEquivalentable(QList<QGraphicsItem *> items);
    void setSeriesEquivalent(QList<QGraphicsItem *> &items);
    void setParallelEquivalent(QList<QGraphicsItem *> &items);
    QVector<ItemGoMarkovOperator*>* operatorItems() const;
    QVector<ItemGoMarkovEquivalent*>* equivalentItems() const;
    QVector<ItemDrawable*>* items() const;
    QVector<ItemGoSignal*>* input() const;
    QVector<QVector<ItemGoSignal*>*>* output() const;
    GoMarkovEquivalent* model() const;
    GoMarkovOperator *getEquivalentOperator();
    ItemGoMarkovOperator *getEquivalentOperatorItem();
    QPointF end();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void move(QGraphicsSceneMouseEvent *event);
    void updateBoundary();
    ItemGoMarkovEquivalent* copy() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    void bindOperators(QList<ItemGoMarkovOperator *> &operatorList, QList<ItemGoMarkovEquivalent *> &equivalentList);

protected:
    QVector<ItemGoMarkovOperator*> *_operatorItems;
    QVector<ItemGoMarkovEquivalent*> *_equivalentItems;
    QVector<ItemDrawable*> *_items;
    ItemGoMarkovEquivalent* _fatherEquivalent;
    GoMarkovEquivalent *_model;
    QPointF _end;
    void removeUnnecessaryItems(QList<QGraphicsItem*> &items);
    QList<ItemDrawable *> getSeriesList(QList<QGraphicsItem*> &items);
    QList<ItemDrawable *> getParallelList(QList<QGraphicsItem*> &items);
};

#endif // ITEMGOMARKOVEQUIVALENT_H
