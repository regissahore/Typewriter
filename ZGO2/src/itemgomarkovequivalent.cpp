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
    this->_operatorItems = new QVector<ItemGOMarkovOperator*>();
    this->_equivalentItems = new QVector<ItemGOMarkovEquivalent*>();
    this->_items = new QVector<ItemDrawable*>();
    this->_model = 0L;
    this->_fatherEquivalent = 0L;
    this->setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT);
}

void ItemGOMarkovEquivalent::setId(const int id)
{
    this->IdentifiedItem::setId(id);
    if (this->_model != 0L)
    {
        this->_model->setId(id);
    }
}

ItemGOMarkovEquivalent::~ItemGOMarkovEquivalent()
{
    for (int i = 0; i < this->_operatorItems->size(); ++i)
    {
        this->_operatorItems->at(i)->setFatherEquivalent(0L);
    }
    this->_operatorItems->clear();
    delete this->_operatorItems;
    for (int i = 0; i < this->_equivalentItems->size(); ++i)
    {
        this->_equivalentItems->at(i)->setFatherEquivalent(0L);
    }
    this->_equivalentItems->clear();
    delete this->_equivalentItems;
    this->_items->clear();
    delete this->_items;
    if (this->model() != 0L)
    {
        delete this->_model;
    }
}

ItemGOMarkovEquivalent* ItemGOMarkovEquivalent::fatherEquivalent() const
{
    return this->_fatherEquivalent;
}

ItemGOMarkovEquivalent* ItemGOMarkovEquivalent::rootEquivalent() const
{
    if (this->fatherEquivalent() != 0L)
    {
        ItemGOMarkovEquivalent *eq = this->fatherEquivalent();
        while (eq->fatherEquivalent() != 0L)
        {
            eq = eq->fatherEquivalent();
        }
        return eq;
    }
    return 0L;
}

void ItemGOMarkovEquivalent::setFatherEquivalent(ItemGOMarkovEquivalent *equivalent)
{
    this->_fatherEquivalent = equivalent;
}

/**
 * Get the series list, the input is considered to be correct.
 * @param items The list of ItemGOMarkovOperator.
 * @return The series list.
 */
QList<ItemDrawable *> ItemGOMarkovEquivalent::getSeriesList(QList<QGraphicsItem*> &items)
{
    QList<ItemDrawable*> list;
    ItemDrawable *source = (ItemDrawable*)items.at(0);
    list.push_back(source);
    ItemDrawable *iterator = source;
    while (true)
    {
        if (iterator->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOMarkovOperator* item = (ItemGOMarkovOperator*)iterator;
            ItemGOSignal *signal = item->input()->at(0);
            if (signal == 0L)
            {
                break;
            }
            iterator = signal->start()->op;
        }
        else if (iterator->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            ItemGOMarkovEquivalent* item = (ItemGOMarkovEquivalent*)iterator;
            ItemGOSignal *signal = item->input()->at(0);
            if (signal == 0L)
            {
                break;
            }
            iterator = signal->start()->op;
        }
        else
        {
            break;
        }
        if (iterator->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            if (((ItemGOMarkovOperator*)iterator)->fatherEquivalent() != 0L)
            {
                iterator = ((ItemGOMarkovOperator*)iterator)->fatherEquivalent();
            }
        }
        if (iterator->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            while (((ItemGOMarkovEquivalent*)iterator)->fatherEquivalent() != 0L)
            {
                iterator = ((ItemGOMarkovEquivalent*)iterator)->fatherEquivalent();
            }
        }
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
        list.push_front(iterator);
    }
    iterator = source;
    while (true)
    {
        if (iterator->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)iterator;
            if (item->output()->at(0)->size() == 0)
            {
                break;
            }
            iterator = item->output()->at(0)->at(0)->end()->op;
        }
        else if (iterator->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            ItemGOMarkovEquivalent *item = (ItemGOMarkovEquivalent*)iterator;
            if (item->output()->at(0)->size() == 0)
            {
                break;
            }
            iterator = item->output()->at(0)->at(0)->end()->op;
        }
        else
        {
            break;
        }
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
        list.push_back(iterator);
    }
    return list;
}

QList<ItemDrawable *> ItemGOMarkovEquivalent::getParallelList(QList<QGraphicsItem*> &items)
{
    QList<ItemDrawable*> list;
    ItemGOMarkovOperator *source = 0L;
    for (int i = 0; i < items.size(); ++i)
    {
        if (((ItemDrawable*)items.at(i))->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOMarkovOperator* item = (ItemGOMarkovOperator*)items.at(i);
            if (item->input()->size() > 1)
            {
                source = item;
                break;
            }
        }
    }
    if (source == 0L)
    {
        return list;
    }
    for (int i = 0; i < source->input()->size(); ++i)
    {
        list.push_back(0L);
    }
    list.push_back(source);
    for (int i = 0; i < source->input()->size(); ++i)
    {
        ItemDrawable *temp = source->input()->at(i)->start()->op;
        int index = -1;
        for (int j = 0; j < items.size(); ++j)
        {
            if (items[j] == temp)
            {
                index = j;
                break;
            }
            if (temp->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
            {
                ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)temp;
                ItemGOMarkovEquivalent *father = op->fatherEquivalent();
                ItemGOMarkovEquivalent *child = 0L;
                while (father != 0L)
                {
                    child = father;
                    father = father->fatherEquivalent();
                }
                if (items[j] == child)
                {
                    index = j;
                    break;
                }
            }
            else
            {
                ItemGOMarkovEquivalent *eq = (ItemGOMarkovEquivalent*)temp;
                ItemGOMarkovEquivalent *father = eq->fatherEquivalent();
                ItemGOMarkovEquivalent *child = 0L;
                while (father != 0L)
                {
                    child = father;
                    father = father->fatherEquivalent();
                }
                if (items[j] == child)
                {
                    index = j;
                    break;
                }
            }
        }
        if (index != -1)
        {
            list[i] = (ItemDrawable*)items[index];
        }
        else
        {
            break;
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
        if (((ItemDrawable*)items.at(i))->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
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
        if (((ItemDrawable*)items.at(i))->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
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
    }
    QList<ItemDrawable*> list = this->getParallelList(items);
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
    QList<ItemDrawable*> list = this->getSeriesList(items);
    this->_operatorItems->clear();
    this->_equivalentItems->clear();
    for (int i = 0; i < list.size(); ++i)
    {
        ItemDrawable *item = list.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            this->_operatorItems->push_back((ItemGOMarkovOperator*)list.at(i));
            ((ItemGOMarkovOperator*)list.at(i))->setFatherEquivalent(this);
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            this->_equivalentItems->push_back((ItemGOMarkovEquivalent*)list.at(i));
            ((ItemGOMarkovEquivalent*)list.at(i))->setFatherEquivalent(this);
        }
        this->items()->push_back(list.at(i));
    }
    this->updateBoundary();
    this->_model = new GOMarkovEquivalentSeries();
    this->_model->setId(this->id());
    for (int i = 0; i < list.size(); ++i)
    {
        if (list.at(i)->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)list.at(i);
            this->model()->operators()->push_back((GOMarkovOperator*)item->model());
        }
        else if (list.at(i)->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            ItemGOMarkovEquivalent *item = (ItemGOMarkovEquivalent*)list.at(i);
            this->model()->operators()->push_back(item->getEquivalentOperator());
        }
    }
}

void ItemGOMarkovEquivalent::setParallelEquivalent(QList<QGraphicsItem *> &items)
{
    this->removeUnnecessaryItems(items);
    QList<ItemDrawable*> list = this->getParallelList(items);
    this->_operatorItems->clear();
    this->_equivalentItems->clear();
    for (int i = 0; i < list.size(); ++i)
    {
        ItemDrawable *item = list.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            this->_operatorItems->push_back((ItemGOMarkovOperator*)list.at(i));
            ((ItemGOMarkovOperator*)list.at(i))->setFatherEquivalent(this);
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            this->_equivalentItems->push_back((ItemGOMarkovEquivalent*)list.at(i));
            ((ItemGOMarkovEquivalent*)list.at(i))->setFatherEquivalent(this);
        }
        this->items()->push_back(list.at(i));
    }
    this->updateBoundary();
    this->_model = new GOMarkovEquivalentParallel();
    this->_model->setId(this->id());
    for (int i = 0; i < list.size(); ++i)
    {
        if (list.at(i)->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)list.at(i);
            this->model()->operators()->push_back((GOMarkovOperator*)item->model());
        }
        else if (list.at(i)->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            ItemGOMarkovEquivalent *item = (ItemGOMarkovEquivalent*)list.at(i);
            this->model()->operators()->push_back(item->getEquivalentOperator());
        }
    }
}

QVector<ItemGOMarkovOperator*>* ItemGOMarkovEquivalent::operatorItems() const
{
    return this->_operatorItems;
}

QVector<ItemGOMarkovEquivalent*>* ItemGOMarkovEquivalent::equivalentItems() const
{
    return this->_equivalentItems;
}

QVector<ItemDrawable*>* ItemGOMarkovEquivalent::items() const
{
    return this->_items;
}

QVector<ItemGOSignal*>* ItemGOMarkovEquivalent::input() const
{
    if (this->_items->size() > 0)
    {
        ItemDrawable *item = this->items()->at(0);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            return ((ItemGOMarkovOperator*)item)->input();
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            return ((ItemGOMarkovEquivalent*)item)->input();
        }
    }
    return 0L;
}

QVector<QVector<ItemGOSignal*>*>* ItemGOMarkovEquivalent::output() const
{
    if (this->_items->size() > 0)
    {
        ItemDrawable *item = this->items()->at(this->items()->size() - 1);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            return ((ItemGOMarkovOperator*)item)->output();
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            return ((ItemGOMarkovEquivalent*)item)->output();
        }
    }
    return 0L;
}

GOMarkovEquivalent* ItemGOMarkovEquivalent::model() const
{
    return this->_model;
}

GOMarkovOperator* ItemGOMarkovEquivalent::getEquivalentOperator()
{
    GOMarkovStatus status = this->model()->getEquivalentStatus();
    GOMarkovOperator *op = GOMarkovOperatorFactory::produce(GOMarkovOperatorFactory::Operator_Type_1);
    op->setId(this->id());
    op->status()->setProbability(1, status.probabilityNormal());
    op->status()->setProbability(2, status.probabilityBreakdown());
    op->markovStatus()->setFrequencyBreakdown(status.frequencyBreakdown());
    op->markovStatus()->setFrequencyRepair(status.frequencyRepair());
    return op;
}

ItemGOMarkovOperator *ItemGOMarkovEquivalent::getEquivalentOperatorItem()
{
    ItemGOMarkovOperator *item = new ItemGOMarkovOperator();
    item->setModel(this->getEquivalentOperator());
    return item;
}

void ItemGOMarkovEquivalent::move(QGraphicsSceneMouseEvent *event)
{
    this->ItemMoveable::move(event);
    if (this->fatherEquivalent() != 0L)
    {
        this->fatherEquivalent()->updateBoundary();
    }
}



void ItemGOMarkovEquivalent::removeUnnecessaryItems(QList<QGraphicsItem*> &items)
{
    for (int i = items.size() - 1; i >= 0; --i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        switch (item->TypedItem::type())
        {
        case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR:
            if (((ItemGOMarkovOperator*)item)->fatherEquivalent() != 0L)
            {
                items.removeAt(i);
                break;
            }
            break;
        case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT:
            if (((ItemGOMarkovEquivalent*)item)->fatherEquivalent() != 0L)
            {
                items.removeAt(i);
            }
            break;
        default:
            items.removeAt(i);
            break;
        }
    }
}

QRectF ItemGOMarkovEquivalent::boundingRect() const
{
    return QRectF(0, 0, this->_end.x(), this->_end.y());
}

void ItemGOMarkovEquivalent::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::NoBrush);
    QFont font;
    font.setPixelSize(16);
    painter->setFont(font);
    painter->drawRoundedRect(0, 0, this->_end.x(), this->_end.y(), 10, 10);
    painter->drawText(QRectF(5, 5, 100, 100), Qt::AlignTop | Qt::AlignLeft, QString("%1").arg(this->id()));
}

QPointF ItemGOMarkovEquivalent::end()
{
    return this->_end;
}

void ItemGOMarkovEquivalent::updateBoundary()
{
    qreal left = 2000000000;
    qreal right = -2000000000;
    qreal top = 2000000000;
    qreal bottom = -2000000000;
    for (int i = 0; i < this->operatorItems()->size(); ++i)
    {
        if (this->operatorItems()->at(i)->x() - 30 < left)
        {
            left = this->operatorItems()->at(i)->x() - 30;
        }
        if (this->operatorItems()->at(i)->x() + 30 > right)
        {
            right = this->operatorItems()->at(i)->x() + 30;
        }
        if (this->operatorItems()->at(i)->y() - 30 < top)
        {
            top = this->operatorItems()->at(i)->y() - 30;
        }
        if (this->operatorItems()->at(i)->y() + 30 > bottom)
        {
            bottom = this->operatorItems()->at(i)->y() + 30;
        }
    }
    for (int i = 0; i < this->equivalentItems()->size(); ++i)
    {
        if (this->equivalentItems()->at(i)->x() - 10 < left)
        {
            left = this->equivalentItems()->at(i)->x() - 10;
        }
        if (this->equivalentItems()->at(i)->x() + this->equivalentItems()->at(i)->end().x() + 10 > right)
        {
            right = this->equivalentItems()->at(i)->x() + this->equivalentItems()->at(i)->end().x() + 10;
        }
        if (this->equivalentItems()->at(i)->y() - 10 < top)
        {
            top = this->equivalentItems()->at(i)->y() - 10;
        }
        if (this->equivalentItems()->at(i)->y() + this->equivalentItems()->at(i)->end().y() + 10 > bottom)
        {
            bottom = this->equivalentItems()->at(i)->y() + this->equivalentItems()->at(i)->end().y() + 10;
        }
    }
    qreal width = right - left;
    qreal height = bottom - top;
    this->setPos(left, top);
    this->_end.setX(width);
    this->_end.setY(height);
    this->prepareGeometryChange();
    if (this->fatherEquivalent() != 0L)
    {
        this->fatherEquivalent()->updateBoundary();
    }
}

ItemGOMarkovEquivalent* ItemGOMarkovEquivalent::copy() const
{
    ItemGOMarkovEquivalent* eq = new ItemGOMarkovEquivalent();
    return eq;
}

void ItemGOMarkovEquivalent::save(QDomDocument &document, QDomElement &root)
{
    if (this->model() == 0L)
    {
        return;
    }
    QDomElement element = document.createElement("equivalent");
    element.setAttribute("x", this->x());
    element.setAttribute("y", this->y());
    element.setAttribute("width", this->_end.x());
    element.setAttribute("height", this->_end.y());
    element.setAttribute("id", this->id());
    element.setAttribute("I", this->model()->I());
    element.setAttribute("L", this->model()->L());
    element.setAttribute("J", this->model()->J());
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
    this->_model->setId(this->id());
    this->_model->setI(root.attribute("I").toInt());
    this->_model->setL(root.attribute("L").toInt());
    this->_model->setJ(root.attribute("J").toInt());
    return true;
}

void ItemGOMarkovEquivalent::bindOperators(QList<ItemGOMarkovOperator*> &operatorList, QList<ItemGOMarkovEquivalent*> &equivalentList)
{
    if (this->model() != 0L)
    {
        this->operatorItems()->clear();
        this->equivalentItems()->clear();
        this->items()->clear();
        this->model()->operators()->clear();
        for (int i = 0; i < this->model()->idList()->size(); ++i)
        {
            int id = this->model()->idList()->at(i);
            for (int j = 0; j < operatorList.size(); ++j)
            {
                if (operatorList[j]->model()->id() == id)
                {
                    this->model()->operators()->push_back((GOMarkovOperator*)operatorList[j]->model());
                    operatorList[j]->setFatherEquivalent(this);
                    this->operatorItems()->push_back(operatorList[j]);
                    this->items()->push_back(operatorList[j]);
                    break;
                }
            }
            for (int j = 0; j < equivalentList.size(); ++j)
            {
                if (equivalentList[j]->model()->id() == id)
                {
                    this->model()->operators()->push_back(equivalentList[j]->getEquivalentOperator());
                    equivalentList[j]->setFatherEquivalent(this);
                    this->equivalentItems()->push_back(equivalentList[j]);
                    this->items()->push_back(equivalentList[j]);
                    break;
                }
            }
        }
    }
}
