#ifndef ITEMGOFACTORY_H
#define ITEMGOFACTORY_H
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Messager;
class ItemDrawable;
class ItemGOOperator;
class ItemGOSignal;
class ItemMoveable;

class ItemGOFactory
{
public:
    static ItemGOOperator* produceOperator(int type);
    static ItemGOSignal* produceSignal();
    static void deleteItem(ItemDrawable *item);
    static void deleteItems(QList<ItemDrawable*> items);
    static void deleteItems(QList<QGraphicsItem*> items);
    static void sendSelectionMessage(Messager *messager, ItemDrawable *item);
};

#endif // ITEMGOFACTORY_H
