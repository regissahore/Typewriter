#include "toolgomarkovequivalent.h"
#include "itemgomarkovoperator.h"
#include "itemgomarkovequivalent.h"
#include "gomarkovoperator.h"
#include "gomarkovequivalent.h"
#include "scenego.h"
#include "definationeditorselectiontype.h"

ToolGOMarkovEquivalent::ToolGOMarkovEquivalent(SceneGO *sceneGO) : ToolGOSelect(sceneGO)
{
}

void ToolGOMarkovEquivalent::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    QList<QGraphicsItem *> items;
    float x, y, width, height;
    switch (this->_status)
    {
    case Status_Selecting:
        if (this->_selection->end().x() >= 0)
        {
            x = this->_selection->pos().x();
            width = this->_selection->end().x();
        }
        else
        {
            x = this->_selection->pos().x() + this->_selection->end().x();
            width = -this->_selection->end().x();
        }
        if (this->_selection->end().y() >= 0)
        {
            y = this->_selection->pos().y();
            height = this->_selection->end().y();
        }
        else
        {
            y = this->_selection->pos().y() + this->_selection->end().y();
            height = -this->_selection->end().y();
        }
        items = this->graphicsScene()->items(QRectF(x, y, width, height),
                                             Qt::IntersectsItemBoundingRect);
        this->_items.clear();
        for (int i = 0; i < items.size(); ++i)
        {
            if (items[i] == this->_selection)
            {
                continue;
            }
            if (((ItemDrawable*)items[i])->isSelectable(this->_selection->pos().x(),
                                                      this->_selection->pos().y(),
                                                      this->_selection->end().x(),
                                                      this->_selection->end().y()))
            {
                this->_items.push_back(items[i]);
            }
        }
        this->addEquivalent();
        this->_selection->setVisible(false);
        this->_selection->update();
        this->_status = Status_Null;
        break;
    default:
        break;
    }
    items.clear();
}

void ToolGOMarkovEquivalent::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void ToolGOMarkovEquivalent::addEquivalent()
{
    ItemGOMarkovEquivalent *equivalent = new ItemGOMarkovEquivalent();
    QVector<bool> visit;
    QList<QGraphicsItem*> items = this->sceneGO()->items();
    for (int i = 0; i <= items.size() + 1; ++i)
    {
        visit.push_back(false);
    }
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            visit[((ItemGOMarkovOperator*)item)->model()->id()] = true;
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            visit[((ItemGOMarkovEquivalent*)item)->model()->id()] = true;
        }
    }
    for (int i = 1; i <= items.size() + 1; ++i)
    {
        if (!visit[i])
        {
            equivalent->setId(i);
            break;
        }
    }
    if (equivalent->isSeriesEquivalentable(this->_items))
    {
        equivalent->setSeriesEquivalent(this->_items);
    }
    else if (equivalent->isParallelEquivalentable(this->_items))
    {
        equivalent->setParallelEquivalent(this->_items);
    }
    if (equivalent->model() == 0L)
    {
        delete equivalent;
    }
    else
    {
        this->graphicsScene()->addItem(equivalent);
    }
}
