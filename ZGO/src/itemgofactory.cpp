#include <QtAlgorithms>
#include "messager.h"
#include "itemgosignal.h"
#include "itemgofactory.h"
#include "itemgooperator.h"
#include "itemgomarkovoperator.h"
#include "itemgomarkovequivalent.h"
#include "gooperatorfactory.h"
#include "messagefactory.h"
#include "definationeditorselectiontype.h"
#include "itemgomarkovcommoncause.h"
#include "itemgomarkovcommoncause2.h"

ItemGOOperator* ItemGOFactory::produceOperator(int type)
{
    ItemGOOperator *item = new ItemGOOperator();
    GOOperator* model = GOOperatorFactory::produce(type);
    item->setModel(model);
    return item;
}

ItemGOSignal* ItemGOFactory::produceSignal()
{
    ItemGOSignal *item = new ItemGOSignal();
    return item;
}

void ItemGOFactory::deleteItem(ItemDrawable *item)
{
    if (item == 0L)
    {
        return;
    }
    int type = item->TypedItem::type();
    if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR || type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
    {
        QList<ItemGOSignal*> signal = ((ItemGOOperator*)item)->getConnectedSignals();
        for (int i = 0; i < signal.size(); ++i)
        {
            deleteItem(signal[i]);
        }
        if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)item;
            if (op->fatherEquivalent() != 0L)
            {
                deleteItem(op->fatherEquivalent());
            }
            if (op->fatherCommonCause() != 0L)
            {
                deleteItem(op->fatherCommonCause());
            }
            if (op->fatherCommonCause2() != 0L)
            {
                deleteItem(op->fatherCommonCause2());
            }
        }
    }
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
    {
        ((ItemGOSignal*)item)->removeConnection();
    }
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
    {
        ItemGOMarkovEquivalent *eq = (ItemGOMarkovEquivalent*)item;
        if (eq->fatherEquivalent() != 0L)
        {
            deleteItem(eq->fatherEquivalent());
        }
    }
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
    {
        ItemGOMarkovCommonCause *common = (ItemGOMarkovCommonCause*)item;
        for (int i = 0; i < common->operatorItems()->size(); ++i)
        {
            common->operatorItems()->at(i)->setFatherCommonCause(0L);
        }
    }
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE_2)
    {
        ItemGOMarkovCommonCause2 *common = (ItemGOMarkovCommonCause2*)item;
        for (int i = 0; i < common->operatorItems()->size(); ++i)
        {
            common->operatorItems()->at(i)->setFatherCommonCause2(0L);
        }
    }
    delete item;
}

void ItemGOFactory::deleteItems(QList<ItemDrawable*> items)
{
    QList<ItemGOSignal*> allSignal;
    QList<ItemGOSignal*> selectedSignal;
    for (int i = 0; i < items.size(); ++i)
    {
        int type = items[i]->TypedItem::type();
        if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR || type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
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
            items[i] = 0L;
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            items[i] = 0L;
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
        {
            items[i] = 0L;
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_TEXT)
        {
        }
        else
        {
            items[i] = 0L;
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
            while (j < selectedSignal.size() - 1 && selectedSignal[j] < allSignal[i])
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
    allSignal.clear();
    selectedSignal.clear();
}

void ItemGOFactory::deleteItems(QList<QGraphicsItem *> items)
{
    QList<ItemDrawable*> drawableItems;
    for (int i = 0; i < items.size(); ++i)
    {
        drawableItems.push_back((ItemDrawable*) items[i]);
    }
    ItemGOFactory::deleteItems(drawableItems);
}

void ItemGOFactory::sendSelectionMessage(Messager *messager, ItemDrawable *item)
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
    message->setMessage(item);
    messager->sendMessage(message);
}

