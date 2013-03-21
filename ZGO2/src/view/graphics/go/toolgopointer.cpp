#include "toolgopointer.h"
#include "scenego.h"

/**
 * Set the graphics drag mode to pointer.
 * @param sceneGO The SceneGO entity.
 */
ToolGOPointer::ToolGOPointer(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->_item = 0L;
    this->setMoving(false);
}

/**
 * Select a item if there exist one.
 * @param Mouse event.
 */
void ToolGOPointer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    ItemDrawable* drawable = (ItemDrawable*)this->graphicsScene()->itemAt(event->scenePos().x(), event->scenePos().y());
    if (0L == drawable)
    {
        setMoving(false);
    }
    else if (!drawable->moveable())
    {
        setMoving(false);
    }
    else
    {
        this->_item = (ItemMoveable*)drawable;
        setMoving(true);
        MessageFactoryEditor *factory = new MessageFactoryEditor();
        MessageEditorSelection* message = (MessageEditorSelection*)factory->produce(MessageFactoryEditor::EDITOR_SELECTION);
        message->setType(this->_item->TypedItem::type());
        message->setMessage(this->_item);
        this->sceneGO()->sendMessage(message);
        delete factory;
        switch (this->_item->TypedItem::type())
        {
        case DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR:
            ((ItemGOOperator*)this->_item)->startMove(event);
            break;
        default:
            this->_item->startMove(event);
            break;
        }
    }
}


/**
 * Move the item if one item is selected.
 * @param Mouse event.
 */
void ToolGOPointer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_moving)
    {
        switch (this->_item->TypedItem::type())
        {
        case DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR:
            ((ItemGOOperator*)this->_item)->move(event);
            break;
        default:
            this->_item->move(event);
            break;
        }

        this->_item->move(event);
    }
}

/**
 * Stop moving if it is moving.
 * @param event Mouse event.
 */
void ToolGOPointer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_moving)
    {
        switch (this->_item->TypedItem::type())
        {
        case DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR:
            ((ItemGOOperator*)this->_item)->stopMove(event);
            break;
        default:
            this->_item->stopMove(event);
            break;
        }
        setMoving(false);
    }
}

/**
 * Set if the item is moving, it will set the cursor at the same time.
 * @param value The boolean value.
 */
void ToolGOPointer::setMoving(bool value)
{
    this->_moving = value;
    if (value)
    {
        this->graphicsView()->setCursor(Qt::SizeAllCursor);
    }
    else
    {
        this->graphicsView()->setCursor(Qt::ArrowCursor);
    }
}
