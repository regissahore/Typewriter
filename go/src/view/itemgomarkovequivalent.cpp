#include "ItemGoMarkovEquivalent.h"
#include "ItemGoMarkovOperator.h"
#include "ItemGoMarkovEquivalent.h"
#include "ItemDrawable.h"
#include "ItemGoSignal.h"
#include "GoOperator.h"
#include "GoMarkovOperator.h"
#include "GoMarkovEquivalentSeries.h"
#include "GoMarkovEquivalentParallel.h"
#include "GoMarkovStatus.h"
#include "DefinationEditorSelectionType.h"
#include "GoStatus.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoMarkovOperatorFactory.h"

ItemGoMarkovEquivalent::ItemGoMarkovEquivalent(QGraphicsItem *parent) : ItemMoveable(parent), IdentifiedItem()
{
    this->_operatorItems = new QVector<ItemGoMarkovOperator*>();
    this->_equivalentItems = new QVector<ItemGoMarkovEquivalent*>();
    this->_items = new QVector<ItemDrawable*>();
    this->_model = 0L;
    this->_fatherEquivalent = 0L;
    this->setType(DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT);
}

void ItemGoMarkovEquivalent::setId(const int id)
{
    this->IdentifiedItem::setId(id);
    if (this->_model != 0L)
    {
        this->_model->setId(id);
    }
}

ItemGoMarkovEquivalent::~ItemGoMarkovEquivalent()
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

ItemGoMarkovEquivalent* ItemGoMarkovEquivalent::fatherEquivalent() const
{
    return this->_fatherEquivalent;
}

ItemGoMarkovEquivalent* ItemGoMarkovEquivalent::rootEquivalent() const
{
    if (this->fatherEquivalent() != 0L)
    {
        ItemGoMarkovEquivalent *eq = this->fatherEquivalent();
        while (eq->fatherEquivalent() != 0L)
        {
            eq = eq->fatherEquivalent();
        }
        return eq;
    }
    return 0L;
}

void ItemGoMarkovEquivalent::setFatherEquivalent(ItemGoMarkovEquivalent *equivalent)
{
    this->_fatherEquivalent = equivalent;
}

QList<ItemDrawable *> ItemGoMarkovEquivalent::getSeriesList(QList<QGraphicsItem*> &items)
{
    QList<ItemDrawable*> list;
    ItemDrawable *source = (ItemDrawable*)items.at(0);
    list.push_back(source);
    ItemDrawable *iterator = source;
    while (true)
    {
        if (iterator->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator* item = (ItemGoMarkovOperator*)iterator;
            ItemGoSignal *signal = item->input()->at(0);
            if (signal == 0L)
            {
                break;
            }
            iterator = signal->start()->op;
        }
        else if (iterator->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            ItemGoMarkovEquivalent* item = (ItemGoMarkovEquivalent*)iterator;
            ItemGoSignal *signal = item->input()->at(0);
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
            if (((ItemGoMarkovOperator*)iterator)->fatherEquivalent() != 0L)
            {
                iterator = ((ItemGoMarkovOperator*)iterator)->fatherEquivalent();
            }
        }
        if (iterator->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            while (((ItemGoMarkovEquivalent*)iterator)->fatherEquivalent() != 0L)
            {
                iterator = ((ItemGoMarkovEquivalent*)iterator)->fatherEquivalent();
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
            ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)iterator;
            if (item->output()->at(0)->size() == 0)
            {
                break;
            }
            iterator = item->output()->at(0)->at(0)->end()->op;
        }
        else if (iterator->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            ItemGoMarkovEquivalent *item = (ItemGoMarkovEquivalent*)iterator;
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

QList<ItemDrawable *> ItemGoMarkovEquivalent::getParallelList(QList<QGraphicsItem*> &items)
{
    QList<ItemDrawable*> list;
    ItemGoMarkovOperator *source = 0L;
    for (int i = 0; i < items.size(); ++i)
    {
        if (((ItemDrawable*)items.at(i))->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator* item = (ItemGoMarkovOperator*)items.at(i);
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
                ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)temp;
                ItemGoMarkovEquivalent *father = op->fatherEquivalent();
                ItemGoMarkovEquivalent *child = 0L;
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
                ItemGoMarkovEquivalent *eq = (ItemGoMarkovEquivalent*)temp;
                ItemGoMarkovEquivalent *father = eq->fatherEquivalent();
                ItemGoMarkovEquivalent *child = 0L;
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

bool ItemGoMarkovEquivalent::isSeriesEquivalentable(QList<QGraphicsItem*> items)
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
            ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)items.at(i);
            if (item->model()->TypedItem::type() != GoMarkovOperatorFactory::Operator_Type_1)
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

bool ItemGoMarkovEquivalent::isParallelEquivalentable(QList<QGraphicsItem*> items)
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
            ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)items.at(i);
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
                if (item->model()->TypedItem::type() != GoMarkovOperatorFactory::Operator_Type_1)
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

void ItemGoMarkovEquivalent::setSeriesEquivalent(QList<QGraphicsItem*> &items)
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
            this->_operatorItems->push_back((ItemGoMarkovOperator*)list.at(i));
            ((ItemGoMarkovOperator*)list.at(i))->setFatherEquivalent(this);
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            this->_equivalentItems->push_back((ItemGoMarkovEquivalent*)list.at(i));
            ((ItemGoMarkovEquivalent*)list.at(i))->setFatherEquivalent(this);
        }
        this->items()->push_back(list.at(i));
    }
    this->updateBoundary();
    this->_model = new GoMarkovEquivalentSeries();
    this->_model->setId(this->id());
    for (int i = 0; i < list.size(); ++i)
    {
        if (list.at(i)->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)list.at(i);
            this->model()->operators()->push_back((GoMarkovOperator*)item->model());
        }
        else if (list.at(i)->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            ItemGoMarkovEquivalent *item = (ItemGoMarkovEquivalent*)list.at(i);
            this->model()->operators()->push_back(item->getEquivalentOperator());
        }
    }
}

void ItemGoMarkovEquivalent::setParallelEquivalent(QList<QGraphicsItem *> &items)
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
            this->_operatorItems->push_back((ItemGoMarkovOperator*)list.at(i));
            ((ItemGoMarkovOperator*)list.at(i))->setFatherEquivalent(this);
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            this->_equivalentItems->push_back((ItemGoMarkovEquivalent*)list.at(i));
            ((ItemGoMarkovEquivalent*)list.at(i))->setFatherEquivalent(this);
        }
        this->items()->push_back(list.at(i));
    }
    this->updateBoundary();
    this->_model = new GoMarkovEquivalentParallel();
    this->_model->setId(this->id());
    for (int i = 0; i < list.size(); ++i)
    {
        if (list.at(i)->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)list.at(i);
            this->model()->operators()->push_back((GoMarkovOperator*)item->model());
        }
        else if (list.at(i)->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            ItemGoMarkovEquivalent *item = (ItemGoMarkovEquivalent*)list.at(i);
            this->model()->operators()->push_back(item->getEquivalentOperator());
        }
    }
}

QVector<ItemGoMarkovOperator*>* ItemGoMarkovEquivalent::operatorItems() const
{
    return this->_operatorItems;
}

QVector<ItemGoMarkovEquivalent*>* ItemGoMarkovEquivalent::equivalentItems() const
{
    return this->_equivalentItems;
}

QVector<ItemDrawable*>* ItemGoMarkovEquivalent::items() const
{
    return this->_items;
}

QVector<ItemGoSignal*>* ItemGoMarkovEquivalent::input() const
{
    if (this->_items->size() > 0)
    {
        ItemDrawable *item = this->items()->at(0);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            return ((ItemGoMarkovOperator*)item)->input();
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            return ((ItemGoMarkovEquivalent*)item)->input();
        }
    }
    return 0L;
}

QVector<QVector<ItemGoSignal*>*>* ItemGoMarkovEquivalent::output() const
{
    if (this->_items->size() > 0)
    {
        ItemDrawable *item = this->items()->at(this->items()->size() - 1);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            return ((ItemGoMarkovOperator*)item)->output();
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            return ((ItemGoMarkovEquivalent*)item)->output();
        }
    }
    return 0L;
}

GoMarkovEquivalent* ItemGoMarkovEquivalent::model() const
{
    return this->_model;
}

GoMarkovOperator* ItemGoMarkovEquivalent::getEquivalentOperator()
{
    GoMarkovStatus status = this->model()->getEquivalentStatus();
    GoMarkovOperator *op = GoMarkovOperatorFactory::produce(GoMarkovOperatorFactory::Operator_Type_1);
    op->setId(this->id());
    op->markovStatus()->setFrequencyBreakdown(status.frequencyBreakdown());
    op->markovStatus()->setFrequencyRepair(status.frequencyRepair());
    return op;
}

ItemGoMarkovOperator *ItemGoMarkovEquivalent::getEquivalentOperatorItem()
{
    ItemGoMarkovOperator *item = new ItemGoMarkovOperator();
    item->setModel(this->getEquivalentOperator());
    return item;
}

void ItemGoMarkovEquivalent::move(QGraphicsSceneMouseEvent *event)
{
    this->ItemMoveable::move(event);
    if (this->fatherEquivalent() != 0L)
    {
        this->fatherEquivalent()->updateBoundary();
    }
}



void ItemGoMarkovEquivalent::removeUnnecessaryItems(QList<QGraphicsItem*> &items)
{
    for (int i = items.size() - 1; i >= 0; --i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        switch (item->TypedItem::type())
        {
        case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR:
            if (((ItemGoMarkovOperator*)item)->fatherEquivalent() != 0L)
            {
                items.removeAt(i);
                break;
            }
            break;
        case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT:
            if (((ItemGoMarkovEquivalent*)item)->fatherEquivalent() != 0L)
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

QRectF ItemGoMarkovEquivalent::boundingRect() const
{
    return QRectF(0, 0, this->_end.x(), this->_end.y());
}

void ItemGoMarkovEquivalent::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::NoBrush);
    QFont font;
    font.setPixelSize(16);
    painter->setFont(font);
    painter->drawRoundedRect(0, 0, this->_end.x(), this->_end.y(), 10, 10);
    painter->drawText(QRectF(5, 5, 100, 100), Qt::AlignTop | Qt::AlignLeft, QString("%1").arg(this->id()));
}

QPointF ItemGoMarkovEquivalent::end()
{
    return this->_end;
}

void ItemGoMarkovEquivalent::updateBoundary()
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

ItemGoMarkovEquivalent* ItemGoMarkovEquivalent::copy() const
{
    ItemGoMarkovEquivalent* eq = new ItemGoMarkovEquivalent();
    return eq;
}

void ItemGoMarkovEquivalent::save(QDomDocument &document, QDomElement &root)
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

bool ItemGoMarkovEquivalent::tryOpen(QDomElement &root)
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
        this->_model = new GoMarkovEquivalentSeries();
    }
    else
    {
        this->_model = new GoMarkovEquivalentParallel();
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

void ItemGoMarkovEquivalent::bindOperators(QList<ItemGoMarkovOperator*> &operatorList, QList<ItemGoMarkovEquivalent*> &equivalentList)
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
                if (operatorList[j]->model()->realID() == id)
                {
                    this->model()->operators()->push_back((GoMarkovOperator*)operatorList[j]->model());
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
