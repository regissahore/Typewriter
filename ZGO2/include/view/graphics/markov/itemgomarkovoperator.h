#ifndef ITEMGOMARKOVOPERATOR_H
#define ITEMGOMARKOVOPERATOR_H
/**
 * The GO operator Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "itemgooperator.h"

class ItemGOMarkovEquivalent;

class ItemGOMarkovOperator : public ItemGOOperator
{
public:
    ItemGOMarkovOperator(QGraphicsItem *parent = 0);
    ItemGOMarkovEquivalent* fatherEquivalent() const;
    ItemGOMarkovEquivalent* rootEquivalent() const;
    void setFatherEquivalent(ItemGOMarkovEquivalent* equivalent);
    void move(QGraphicsSceneMouseEvent *event);
    void setModelType(const int type);
    bool tryOpen(QDomElement &root);

protected:
    ItemGOMarkovEquivalent *_fatherEquivalent;
};

#endif // ITEMGOMARKOVOPERATOR_H
