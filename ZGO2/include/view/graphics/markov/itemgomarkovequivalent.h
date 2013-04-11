#ifndef ITEMGOMARKOVEQUIVALENT_H
#define ITEMGOMARKOVEQUIVALENT_H
/**
 * The quivalent of Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "itemmoveable.h"

class QGraphicsItem;
class ItemGOMarkovOperator;
class GOMarkovOperator;
class GOMarkovEquivalent;

class ItemGOMarkovEquivalent : public ItemMoveable
{
public:
    ItemGOMarkovEquivalent(QGraphicsItem *parent = 0);
    ~ItemGOMarkovEquivalent();
    bool isSeriesEquivalentable(QList<QGraphicsItem*> &items);
    bool isParallelEquivalentable(QList<QGraphicsItem*> &items);
    void setSeriesEquivalent(QList<QGraphicsItem*> &items);
    void setParallelEquivalent(QList<QGraphicsItem*> &items);
    QVector<ItemGOMarkovOperator*>* items() const;
    GOMarkovEquivalent* model() const;
    GOMarkovOperator *getEquivalentOperator();
    ItemGOMarkovOperator *getEquivalentOperatorItem();

protected:
    QVector<ItemGOMarkovOperator*> *_items;
    GOMarkovEquivalent *_model;
    void removeUnnecessaryItems(QList<QGraphicsItem*> &items);
    QList<GOMarkovOperator*> getSeriesList(QList<QGraphicsItem*> &items);
    QList<GOMarkovOperator*> getParallelList(QList<QGraphicsItem*> &items);
};

#endif // ITEMGOMARKOVEQUIVALENT_H
