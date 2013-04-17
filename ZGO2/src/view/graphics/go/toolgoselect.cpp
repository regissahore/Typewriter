#include <QtAlgorithms>
#include "toolgoselect.h"
#include "itemgooperator.h"
#include "itemgosignal.h"
#include "itemgofactory.h"
#include "definationeditorselectiontype.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOSelect::ToolGOSelect(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->_selection = new ItemSelection();
    this->graphicsScene()->addItem(this->_selection);
    this->_selection->setVisible(false);
    this->_status = Status_Null;
    this->graphicsView()->setCursor(Qt::ArrowCursor);
}

/**
 * Clear.
 */
ToolGOSelect::~ToolGOSelect()
{
    this->_items.clear();
    this->graphicsScene()->removeItem(this->_selection);
    delete this->_selection;
}

/**
 * Mouse press event.
 * @param event Mouse event.
 */
void ToolGOSelect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->_status)
    {
    case Status_Null:
        this->_status = Status_Selecting;
        this->_selection->setPos(QPoint(event->scenePos().x(),
                                        event->scenePos().y()));
        this->_selection->setEnd(QPoint(0, 0));
        this->_selection->setVisible(true);
        break;
    case Status_Selected:
        if (this->_selection->isInside(event->scenePos().x(),
                                       event->scenePos().y()))
        {
            this->_status = Status_Moving;
            for (int i = 0; i < this->_items.size(); ++i)
            {
                if (((ItemDrawable*)this->_items[i])->moveable())
                {
                    ((ItemMoveable*)this->_items[i])->startMove(event);
                }
            }
            this->_selection->startMove(event);
        }
        else
        {
            this->_status = Status_Null;
            this->_items.clear();
            this->mousePressEvent(event);
        }
        break;
    default:
        break;
    }
}

/**
 * Mouse move event.
 * @param event Mouse event.
 */
void ToolGOSelect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->_status)
    {
    case Status_Selecting:
        this->_selection->setEnd(QPoint(event->scenePos().x() - this->_selection->pos().x(),
                                        event->scenePos().y() - this->_selection->pos().y()));
        this->_selection->update();
        break;
    case Status_Selected:
        if (this->_selection->isInside(event->scenePos().x(), event->scenePos().y()))
        {
            this->graphicsView()->setCursor(Qt::SizeAllCursor);
        }
        else
        {
            this->graphicsView()->setCursor(Qt::ArrowCursor);
        }
        break;
    case Status_Moving:
        for (int i = 0; i < this->_items.size(); ++i)
        {
            if (((ItemDrawable*)this->_items[i])->moveable())
            {
                ((ItemMoveable*)this->_items[i])->move(event);
            }
        }
        this->_selection->move(event);
        break;
    default:
        break;
    }
}

/**
 * Mouse release event.
 * @param event Mouse event.
 */
void ToolGOSelect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem *> items;
    float x, y, width, height;
    switch (this->_status)
    {
    case Status_Selecting:
        this->_status = Status_Selected;
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
        break;
    case Status_Moving:
        for (int i = 0; i < this->_items.size(); ++i)
        {
            if (((ItemDrawable*)this->_items[i])->moveable())
            {
                ((ItemMoveable*)this->_items[i])->stopMove(event);
            }
        }
        this->_selection->stopMove(event);
        this->_status = Status_Selected;
        break;
    default:
        break;
    }
    items.clear();
}

/**
 * Key Release event.
 * @param event Key event.
 */
void ToolGOSelect::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        ItemGOFactory::deleteItems(this->_items);
        this->_items.clear();
    }
}
