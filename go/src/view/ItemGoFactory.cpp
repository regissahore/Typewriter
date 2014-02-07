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
using namespace std;

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
    if (item == nullptr)
    {
        return;
    }
    int type = item->TypedItem::type();
    if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR || type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
    {
        QList<ItemGoSignal*> signal = ((ItemGoOperator*)item)->getConnectedSignals();
        for (int i = 0; i < signal.size(); ++i)
        {
            deleteItem(signal[i]);
        }
        if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
            if (op->fatherEquivalent() != nullptr)
            {
                deleteItem(op->fatherEquivalent());
            }
            if (op->fatherCommonCause() != nullptr)
            {
                deleteItem(op->fatherCommonCause());
            }
            if (op->fatherCommonCause2() != nullptr)
            {
                deleteItem(op->fatherCommonCause2());
            }
        }
    }
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
    {
        ((ItemGoSignal*)item)->removeConnection();
    }
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
    {
        ItemGoMarkovEquivalent *eq = (ItemGoMarkovEquivalent*)item;
        if (eq->fatherEquivalent() != nullptr)
        {
            deleteItem(eq->fatherEquivalent());
        }
    }
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
    {
        ItemGoMarkovCommonCause *common = (ItemGoMarkovCommonCause*)item;
        for (int i = 0; i < common->operatorItems()->size(); ++i)
        {
            common->operatorItems()->at(i)->setFatherCommonCause(nullptr);
        }
    }
    else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE_2)
    {
        ItemGoMarkovCommonCause2 *common = (ItemGoMarkovCommonCause2*)item;
        for (int i = 0; i < common->operatorItems()->size(); ++i)
        {
            common->operatorItems()->at(i)->setFatherCommonCause2(nullptr);
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
        if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR || type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            QList<ItemGoSignal*> signal = ((ItemGoOperator*)items[i])->getConnectedSignals();
            for (int j = 0; j < signal.size(); ++j)
            {
                allSignal.push_back(signal[j]);
            }
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            selectedSignal.push_back((ItemGoSignal*)items[i]);
            items[i] = nullptr;
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            items[i] = nullptr;
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
        {
            items[i] = nullptr;
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_TEXT)
        {
        }
        else
        {
            items[i] = nullptr;
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
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
    message->setMessage(item);
    messager->sendMessage(message);
}

