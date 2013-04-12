#ifndef ITEMGOMARKOVEQUIVALENT_H
#define ITEMGOMARKOVEQUIVALENT_H
/**
 * The quivalent of Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "itemmoveable.h"
#include "identifieditem.h"
#include "domitem.h"

class QGraphicsItem;
class ItemGOSignal;
class ItemGOMarkovOperator;
class GOMarkovOperator;
class GOMarkovEquivalent;

class ItemGOMarkovEquivalent : public ItemMoveable, public IdentifiedItem
{
public:
    ItemGOMarkovEquivalent(QGraphicsItem *parent = 0);
    ~ItemGOMarkovEquivalent();
    ItemGOMarkovEquivalent* fatherEquivalent() const;
    void setFatherEquivalent(ItemGOMarkovEquivalent *equivalent);
    bool isSeriesEquivalentable(QList<QGraphicsItem*> items);
    bool isParallelEquivalentable(QList<QGraphicsItem *> items);
    void setSeriesEquivalent(QList<QGraphicsItem *> &items);
    void setParallelEquivalent(QList<QGraphicsItem *> &items);
    QVector<ItemGOMarkovOperator*>* operatorItems() const;
    QVector<ItemGOMarkovEquivalent*>* equivalentItems() const;
    QVector<ItemDrawable*>* items() const;
    QVector<ItemGOSignal*>* input() const;
    QVector<QVector<ItemGOSignal*>*>* output() const;
    GOMarkovEquivalent* model() const;
    GOMarkovOperator *getEquivalentOperator();
    QPointF end();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void move(QGraphicsSceneMouseEvent *event);
    void updateBoundary();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    void bindOperators(QList<ItemGOMarkovOperator *> &operatorList, QList<ItemGOMarkovEquivalent *> &equivalentList);

protected:
    QVector<ItemGOMarkovOperator*> *_operatorItems;
    QVector<ItemGOMarkovEquivalent*> *_equivalentItems;
    QVector<ItemDrawable*> *_items;
    ItemGOMarkovEquivalent* _fatherEquivalent;
    GOMarkovEquivalent *_model;
    QPointF _end;
    void removeUnnecessaryItems(QList<QGraphicsItem*> &items);
    QList<ItemDrawable *> getSeriesList(QList<QGraphicsItem*> &items);
    QList<ItemDrawable *> getParallelList(QList<QGraphicsItem*> &items);
};

#endif // ITEMGOMARKOVEQUIVALENT_H
