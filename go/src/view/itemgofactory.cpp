#include <QtAlgorithms>
#include "Messager.h"
#include "ItemGoSignal.h"
#include "ItemGoFactory.h"
#include "ItemGoOperator.h"
#include "ItemGoMarkovOperator.h"
#include "ItemGoMarkovEquivalent.h"
#include "GoOperatorFactory.h"
#include "MessageFactory.h"
#include "DefinationEditorSelectionType.h"
#include "ItemGoMarkovCommonCause.h"
#include "ItemGoMarkovCommonCause2.h"

ItemGoOperator* ItemGoFactory::produceOperator(int type)
{
    ItemGoOperator *item = new ItemGoOperator();
    GoOperator* model = GoOperatorFactory::produce(type);
    item->setModel(model);
    return item;
}

ItemGoSignal* ItemGoFactory::produceSignal()
{
    ItemGoSignal *item = new ItemGoSignal();
    return item;
}

void ItemGoFactory::deleteItem(ItemDrawable *item)
{
    if (item == 0L)
    {
        return;
    }
    int type = item->TypedItem::type();
    if (type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_OPERATOR || type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_MARKOV_OPERATOR)
    {
        QList<ItemGoSignal*> signal = ((ItemGoOperator*)item)->getConnectedSignals();
        for (int i = 0; i < signal.size(); ++i)
        {
            deleteItem(signal[i]);
        }
        if (type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
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
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_SIGNAL)
    {
        ((ItemGoSignal*)item)->removeConnection();
    }
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_MARKOV_EQUIVALENT)
    {
        ItemGoMarkovEquivalent *eq = (ItemGoMarkovEquivalent*)item;
        if (eq->fatherEquivalent() != 0L)
        {
            deleteItem(eq->fatherEquivalent());
        }
    }
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_MARKOV_COMMON_CAUSE)
    {
        ItemGoMarkovCommonCause *common = (ItemGoMarkovCommonCause*)item;
        for (int i = 0; i < common->operatorItems()->size(); ++i)
        {
            common->operatorItems()->at(i)->setFatherCommonCause(0L);
        }
    }
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_MARKOV_COMMON_CAUSE_2)
    {
        ItemGoMarkovCommonCause2 *common = (ItemGoMarkovCommonCause2*)item;
        for (int i = 0; i < common->operatorItems()->size(); ++i)
        {
            common->operatorItems()->at(i)->setFatherCommonCause2(0L);
        }
    }
    delete item;
}

void ItemGoFactory::deleteItems(QList<ItemDrawable*> items)
{
    QList<ItemGoSignal*> allSignal;
    QList<ItemGoSignal*> selectedSignal;
    for (int i = 0; i < items.size(); ++i)
    {
        int type = items[i]->TypedItem::type();
        if (type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_OPERATOR || type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_MARKOV_OPERATOR)
        {
            QList<ItemGoSignal*> signal = ((ItemGoOperator*)items[i])->getConnectedSignals();
            for (int j = 0; j < signal.size(); ++j)
            {
                allSignal.push_back(signal[j]);
            }
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_SIGNAL)
        {
            selectedSignal.push_back((ItemGoSignal*)items[i]);
            items[i] = 0L;
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_MARKOV_EQUIVALENT)
        {
            items[i] = 0L;
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_MARKOV_COMMON_CAUSE)
        {
            items[i] = 0L;
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_Go_TEXT)
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

void ItemGoFactory::deleteItems(QList<QGraphicsItem *> items)
{
    QList<ItemDrawable*> drawableItems;
    for (int i = 0; i < items.size(); ++i)
    {
        drawableItems.push_back((ItemDrawable*) items[i]);
    }
    ItemGoFactory::deleteItems(drawableItems);
}

void ItemGoFactory::sendSelectionMessage(Messager *messager, ItemDrawable *item)
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
    message->setMessage(item);
    messager->sendMessage(message);
}

