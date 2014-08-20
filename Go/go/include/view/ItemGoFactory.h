#ifndef ITEMGOFACTORY_H
#define ITEMGOFACTORY_H
#include "stable.h"

class Messager;
class ItemDrawable;
class ItemGoOperator;
class ItemGoSignal;
class ItemMoveable;

class ItemGoFactory
{
public:
    static ItemGoOperator* produceOperator(int type);
    static ItemGoSignal* produceSignal();
    static void deleteItem(ItemDrawable *item);
    static void deleteItems(QList<ItemDrawable*> items);
    static void deleteItems(QList<QGraphicsItem*> items);
    static void sendSelectionMessage(Messager *messager, ItemDrawable *item);
};

#endif // ITEMGOFACTORY_H
