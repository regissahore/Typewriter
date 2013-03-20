#include "toolgoselect.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOSelect::ToolGOSelect(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->_selection = new ItemSelection();
    this->graphicsScene()->addItem(this->_selection);
    this->_status = Status_Null;
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
        this->_selection->setPos(QPoint(event->scenePos().x(), event->scenePos().y()));
        this->_selection->setEnd(QPoint(0, 0));
        break;
    case Status_Selected:
        if (this->_selection->isInside(event->scenePos().x(), event->scenePos().y()))
        {
            this->_status = Status_Moving;
            for (int i = 0; i < this->_items.size(); ++i)
            {
                ((ItemMoveable*)this->_items[i])->mousePressEvent(event);
            }
            this->_selection->mousePressEvent(event);
        }
        else
        {
            this->_status = Status_Selecting;
            this->_selection->setPos(QPoint(event->scenePos().x(), event->scenePos().y()));
            this->_selection->setEnd(QPoint(0, 0));
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
            ((ItemMoveable*)this->_items[i])->mouseMoveEvent(event);
        }
        this->_selection->mouseMoveEvent(event);
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
    switch (this->_status)
    {
    case Status_Selecting:
        this->_status = Status_Selected;
        this->_items = this->graphicsScene()->items(this->_selection->pos().x(),
                                                    this->_selection->pos().y(),
                                                    this->_selection->end().x(),
                                                    this->_selection->end().y());
        break;
    case Status_Moving:
        for (int i = 0; i < this->_items.size(); ++i)
        {
            ((ItemMoveable*)this->_items[i])->mouseReleaseEvent(event);
        }
        this->_selection->mouseReleaseEvent(event);
        this->_status = Status_Selected;
        break;
    default:
        break;
    }
}
