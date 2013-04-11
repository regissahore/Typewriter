#include "itemgomarkovequivalent.h"
#include "itemgomarkovoperator.h"
#include "itemgomarkovequivalent.h"
#include "itemdrawable.h"
#include "itemgosignal.h"
#include "gooperator.h"
#include "gomarkovoperator.h"
#include "gomarkovequivalentseries.h"
#include "gomarkovequivalentparallel.h"
#include "gomarkovstatus.h"
#include "definationeditorselectiontype.h"
#include "gostatus.h"
#include "goinput.h"
#include "gooutput.h"
#include "gomarkovoperatorfactory.h"

ItemGOMarkovEquivalent::ItemGOMarkovEquivalent(QGraphicsItem *parent) : ItemMoveable(parent)
{
    this->_items = new QVector<ItemGOMarkovOperator*>();
    this->_model = 0L;
}

ItemGOMarkovEquivalent::~ItemGOMarkovEquivalent()
{
    this->_items->clear();
    delete this->_items;
    delete this->_model;
}

/**
 * Get the series list, the input is considered to be correct.
 * @param items The list of ItemGOMarkovOperator.
 * @return The series list.
 */
QList<GOMarkovOperator*> ItemGOMarkovEquivalent::getSeriesList(QList<QGraphicsItem*> &items)
{
    QList<GOMarkovOperator*> list;
    ItemGOMarkovOperator *source = (ItemGOMarkovOperator*)items.at(0);
    list.push_back((GOMarkovOperator*)source->model());
    ItemGOMarkovOperator *iterator = source;
    while (true)
    {
        iterator = (ItemGOMarkovOperator*)iterator->input()->at(0)->start()->op;
        bool appear = false;
        for (int i = 0; i < items.size(); ++i)
        {
            if (items[i] == iterator)
            {
                appear = true;
                break;
            }
        }
        if (!appear)
        {
            break;
        }
        list.push_front((GOMarkovOperator*)iterator->model());
    }
    iterator = source;
    while (true)
    {
        if (iterator->output()->at(0)->size() == 0)
        {
            break;
        }
        iterator = (ItemGOMarkovOperator*)iterator->output()->at(0)->at(0)->end()->op;
        bool appear = false;
        for (int i = 0; i < items.size(); ++i)
        {
            if (items[i] == iterator)
            {
                appear = true;
                break;
            }
        }
        if (!appear)
        {
            break;
        }
        list.push_back((GOMarkovOperator*)iterator->model());
    }
    return list;
}

QList<GOMarkovOperator*> ItemGOMarkovEquivalent::getParallelList(QList<QGraphicsItem*> &items)
{
    QList<GOMarkovOperator*> list;
    ItemGOMarkovOperator *source;
    for (int i = 0; i < items.size(); ++i)
    {
        ItemGOMarkovOperator* item = (ItemGOMarkovOperator*)items.at(i);
        if (item->input()->size() > 1)
        {
            source = item;
            break;
        }
    }
    list.push_back((GOMarkovOperator*)source->model());
    for (int i = 0; i < source->input()->size(); ++i)
    {
        list.push_back(0L);
    }
    for (int i = 0; i < source->input()->size(); ++i)
    {
        ItemGOMarkovOperator *temp = (ItemGOMarkovOperator*)source->input()->at(i)->start()->op;
        bool appear = false;
        for (int j = 0; j < items.size(); ++j)
        {
            if (items[j] == temp)
            {
                appear = true;
                break;
            }
        }
        if (appear)
        {
            list[i + 1] = (GOMarkovOperator*)temp->model();
        }
    }
    return list;
}

bool ItemGOMarkovEquivalent::isSeriesEquivalentable(QList<QGraphicsItem*> &items)
{
    this->removeUnnecessaryItems(items);
    if (items.size() <= 1)
    {
        return false;
    }
    int noOutputNumber = 0;
    for (int i = 0; i < items.size(); ++i)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)items.at(i);
        if (item->model()->TypedItem::type() != GOMarkovOperatorFactory::Operator_Type_1)
        {
            return false;
        }
        if (item->input()->size() != 1)
        {
            return false;
        }
        if (item->subInput()->size() != 0)
        {
            return false;
        }
        if (item->output()->size() != 1)
        {
            return false;
        }
        if (item->input()->at(0) == 0L)
        {
            return false;
        }
        if (item->output()->at(0)->size() == 0)
        {
            if (++noOutputNumber > 1)
            {
                return false;
            }
        }
    }
    if (this->getSeriesList(items).size() != items.size())
    {
        return false;
    }
    return true;
}

bool ItemGOMarkovEquivalent::isParallelEquivalentable(QList<QGraphicsItem*> &items)
{
    this->removeUnnecessaryItems(items);
    if (items.size() <= 2)
    {
        return false;
    }
    int multiInputNum = 0;
    for (int i = 0; i < items.size(); ++i)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)items.at(i);
        if (item->input()->size() == 0)
        {
            return false;
        }
        if (item->subInput()->size() != 0)
        {
            return false;
        }
        if (item->output()->size() != 1)
        {
            return false;
        }
        if (item->input()->size() > 1)
        {
            if (++multiInputNum > 1)
            {
                return false;
            }
            for (int j = 0; j < item->input()->size(); ++j)
            {
                if (item->input()->at(j) == 0L)
                {
                    return false;
                }
            }
        }
        else
        {
            if (item->model()->TypedItem::type() != GOMarkovOperatorFactory::Operator_Type_1)
            {
                return false;
            }
            if (item->output()->at(0)->size() == 0)
            {
                return false;
            }
        }
        if (item->input()->at(0) == 0L)
        {
            return false;
        }
    }
    QList<GOMarkovOperator*> list = this->getParallelList(items);
    if (list.size() != items.size())
    {
        return false;
    }
    for (int i = 0; i < list.size(); ++i)
    {
        if (list.at(i) == 0L)
        {
            return false;
        }
    }
    return true;
}

void ItemGOMarkovEquivalent::setSeriesEquivalent(QList<QGraphicsItem*> &items)
{
    this->removeUnnecessaryItems(items);
    this->_model = new GOMarkovEquivalentSeries();
    QList<GOMarkovOperator*> list = this->getSeriesList(items);
    for (int i = 0; i < list.size(); ++i)
    {
        this->model()->operators()->push_back(list.at(i));
    }
}

void ItemGOMarkovEquivalent::setParallelEquivalent(QList<QGraphicsItem*> &items)
{
    this->removeUnnecessaryItems(items);
    this->_model = new GOMarkovEquivalentParallel();
    QList<GOMarkovOperator*> list = this->getParallelList(items);
    for (int i = 0; i < list.size(); ++i)
    {
        this->model()->operators()->push_back(list.at(i));
    }
}

QVector<ItemGOMarkovOperator*>* ItemGOMarkovEquivalent::items() const
{
    return this->_items;
}

GOMarkovEquivalent* ItemGOMarkovEquivalent::model() const
{
    return this->_model;
}
GOMarkovOperator* ItemGOMarkovEquivalent::getEquivalentOperator()
{
    GOMarkovStatus status = this->model()->getEquivalentStatus();
    GOMarkovOperator *op = new GOMarkovOperator();
    op->status()->setProbability(1, status.probabilityNormal());
    op->status()->setProbability(2, status.probabilityBreakdown());
    op->markovStatus()->setProbabilityNormal(status.probabilityNormal());
    op->markovStatus()->setFrequencyBreakdown(status.frequencyBreakdown());
    return op;
}

ItemGOMarkovOperator *ItemGOMarkovEquivalent::getEquivalentOperatorItem()
{
    GOMarkovStatus status = this->model()->getEquivalentStatus();
    ItemGOMarkovOperator *item = new ItemGOMarkovOperator();
    item->setType(GOMarkovOperatorFactory::Operator_Type_1);
    item->model()->status()->setProbability(1, status.probabilityNormal());
    item->model()->status()->setProbability(2, status.probabilityBreakdown());
    ((GOMarkovOperator*)item->model())->markovStatus()->setProbabilityNormal(status.probabilityNormal());
    ((GOMarkovOperator*)item->model())->markovStatus()->setFrequencyBreakdown(status.frequencyBreakdown());
    return item;
}

void ItemGOMarkovEquivalent::removeUnnecessaryItems(QList<QGraphicsItem*> &items)
{
    for (int i = items.size() - 1; i >= 0; --i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() != DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR ||
                item->TypedItem::type() != DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            items.removeAt(i);
            continue;
        }
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            ItemGOMarkovEquivalent *equivalent = (ItemGOMarkovEquivalent*)item;
            for (int j = items.size() - 1; j >= 0; --j)
            {
                for (int k = 0; k < equivalent->items()->size(); ++k)
                {
                    if (items[j] == equivalent->items()->at(k))
                    {
                        items.removeAt(j);
                        if (j < i)
                        {
                            -- i;
                        }
                        break;
                    }
                }
            }
            items[i] = equivalent->getEquivalentOperatorItem();
        }
    }
}
