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

ItemGOMarkovEquivalent::ItemGOMarkovEquivalent(QGraphicsItem *parent) : ItemMoveable(parent), IdentifiedItem()
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

bool ItemGOMarkovEquivalent::isSeriesEquivalentable(QList<QGraphicsItem*> items)
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

bool ItemGOMarkovEquivalent::isParallelEquivalentable(QList<QGraphicsItem*> items)
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
    this->_model->setId(this->id());
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
    this->_model->setId(this->id());
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
    item->model()->setId(this->id());
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

QRectF ItemGOMarkovEquivalent::boundingRect() const
{
    return QRectF(0, 0, this->_end.x(), this->_end.y());
}

void ItemGOMarkovEquivalent::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(0, 0, this->_end.x(), this->_end.y());
    painter->drawText(QRectF(10, 10, 100, 100), Qt::AlignTop | Qt::AlignLeft, QString("%1").arg(this->id()));
}

void ItemGOMarkovEquivalent::updateBoundary()
{
    qreal left = this->items()->at(0)->x();
    qreal right = this->items()->at(0)->x();
    qreal top = this->items()->at(0)->y();
    qreal bottom = this->items()->at(0)->y();
    for (int i = 1; i < this->items()->size(); ++i)
    {
        if (this->items()->at(i)->x() < left)
        {
            left = this->items()->at(i)->x();
        }
        if (this->items()->at(i)->x() > right)
        {
            right = this->items()->at(i)->x();
        }
        if (this->items()->at(i)->y() < top)
        {
            top = this->items()->at(i)->y();
        }
        if (this->items()->at(i)->y() > bottom)
        {
            bottom = this->items()->at(i)->y();
        }
    }
    qreal width = right - left;
    qreal height = bottom - top;
    this->setPos(left, top);
    this->_end.setX(width);
    this->_end.setY(height);
    this->prepareGeometryChange();
}

void ItemGOMarkovEquivalent::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("equivalent");
    element.setAttribute("x", this->x());
    element.setAttribute("y", this->y());
    element.setAttribute("width", this->_end.x());
    element.setAttribute("height", this->_end.y());
    element.setAttribute("id", this->id());
    this->model()->save(document, element);
    root.appendChild(element);
}

bool ItemGOMarkovEquivalent::tryOpen(QDomElement &root)
{
    if (root.tagName() != "equivalent")
    {
        return false;
    }
    this->setPos(root.attribute("x").toFloat(), root.attribute("y").toFloat());
    this->_end.setX(root.attribute("width").toFloat());
    this->_end.setY(root.attribute("height").toFloat());
    this->setId(root.attribute("id").toInt());
    QDomElement element = root.firstChildElement();
    if (element.tagName() == "series")
    {
        this->_model = new GOMarkovEquivalentSeries();
    }
    else
    {
        this->_model = new GOMarkovEquivalentParallel();
    }
    if (this->_model == 0L)
    {
        return false;
    }
    if (!this->_model->tryOpen(element))
    {
        return false;
    }
    return true;
}
