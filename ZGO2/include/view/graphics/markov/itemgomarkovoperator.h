#ifndef ITEMGOMARKOVOPERATOR_H
#define ITEMGOMARKOVOPERATOR_H
/**
 * The GO operator Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "itemgooperator.h"

class ItemGOMarkovOperator : public ItemGOOperator
{
public:
    ItemGOMarkovOperator(QGraphicsItem *parent = 0);
    void setModelType(const int type);
    bool tryOpen(QDomElement &root);
};

#endif // ITEMGOMARKOVOPERATOR_H
