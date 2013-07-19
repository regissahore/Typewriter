#ifndef ITEMGOMARKOVOPERATOR_H
#define ITEMGOMARKOVOPERATOR_H
/**
 * The GO operator Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "itemgooperator.h"

class ItemGOMarkovEquivalent;
class ItemGOMarkovCommonCause;

class ItemGOMarkovOperator : public ItemGOOperator
{
public:
    ItemGOMarkovOperator(QGraphicsItem *parent = 0);
    ItemGOMarkovEquivalent* fatherEquivalent() const;
    ItemGOMarkovEquivalent* rootEquivalent() const;
    void setFatherEquivalent(ItemGOMarkovEquivalent* equivalent);
    ItemGOMarkovCommonCause* fatherCommonCause() const;
    void setFatherCommonCause(ItemGOMarkovCommonCause* commonCause);
    void move(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    void setModelType(const int type);
    bool tryOpen(QDomElement &root);

protected:
    ItemGOMarkovEquivalent *_fatherEquivalent;
    ItemGOMarkovCommonCause *_fatherCommonCause;
};

#endif // ITEMGOMARKOVOPERATOR_H
