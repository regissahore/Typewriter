#ifndef ITEMGOFACTORY_H
#define ITEMGOFACTORY_H
/**
 * A GO item factory.
 * @see DefinationEditorSelectionType
 * The class is static and should not be instantiated.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QList>
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
    static void sendSelectionMessage(Messager *messager, ItemDrawable *item);
};

#endif // ITEMGOFACTORY_H
