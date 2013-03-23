#include <QtAlgorithms>
#include "itemgosignal.h"
#include "itemgofactory.h"
#include "itemgooperator.h"
#include "gooperatorfactory.h"
#include "messagefactoryeditor.h"

/**
 * Produce a GO operator.
 * @param type @see GOOperatorFactory
 * @return The GO operator.
 */
ItemGOOperator* ItemGOFactory::produceOperator(int type)
{
    ItemGOOperator *item = new ItemGOOperator();
    GOOperator* model = GOOperatorFactory::produce(type);
    item->setModel(model);
    return item;
}

/**
 * Produce a GO signal.
 * @return The GO signal.
 */
ItemGOSignal* ItemGOFactory::produceSignal()
{
    ItemGOSignal *item = new ItemGOSignal();
    return item;
}

/**
 * Delete a drawable item.
 * @param item Drawable item.
 */
void ItemGOFactory::deleteItem(ItemDrawable *item)
{
    int type = item->TypedItem::type();
    if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
    {
        QList<ItemGOSignal*> signal = ((ItemGOOperator*)item)->getConnectedSignals();
        for (int i = 0; i < signal.size(); ++i)
        {
            deleteItem(signal[i]);
        }
    }
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
    {
        ((ItemGOSignal*)item)->removeConnection();
    }
    delete item;
}

/**
 * Delete drawable items.
 * @param items Drawable items.
 */
void ItemGOFactory::deleteItems(QList<ItemDrawable*> items)
{
    QList<ItemGOSignal*> allSignal;
    QList<ItemGOSignal*> selectedSignal;
    for (int i = 0; i < items.size(); ++i)
    {
        int type = items[i]->TypedItem::type();
        if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
        {
            QList<ItemGOSignal*> signal = ((ItemGOOperator*)items[i])->getConnectedSignals();
            for (int j = 0; j < signal.size(); ++j)
            {
                allSignal.push_back(signal[j]);
            }
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            selectedSignal.push_back((ItemGOSignal*)items[i]);
        }
    }
    qSort(allSignal.begin(), allSignal.end());
    qSort(selectedSignal.begin(), selectedSignal.end());
    for (int i = 0, j = 0; i < allSignal.size(); ++i)
    {
        if (i > 0)
        {
            if (allSignal[i] == allSignal[i - 1])
            {
                continue;
            }
        }
        if (j < selectedSignal.size())
        {
            while (j < selectedSignal.size() && selectedSignal[j] < allSignal[i])
            {
                ++j;
            }
            if (selectedSignal[j] == allSignal[i])
            {
                continue;
            }
        }
        deleteItem(allSignal[i]);
    }
    for (int i = 0; i < items.size(); ++i)
    {
        deleteItem(items[i]);
    }
}

/**
 * Send the item selection message.
 * @param item The item.
 */
void ItemGOFactory::sendSelectionMessage(Messager *messager, ItemDrawable *item)
{
    MessageFactoryEditor *factory = new MessageFactoryEditor();
    MessageEditorSelection* message = (MessageEditorSelection*)factory->produce(MessageFactoryEditor::EDITOR_SELECTION);
    message->setType(item->TypedItem::type());
    message->setMessage(item);
    messager->sendMessage(message);
    delete factory;
}

