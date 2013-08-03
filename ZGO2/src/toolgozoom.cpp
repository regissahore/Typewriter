#include "toolgozoom.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOZoom::ToolGOZoom(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->graphicsView()->setCursor(Qt::PointingHandCursor);
}

/**
 * Zoom in when ALT is pressed, otherwise zoom out.
 * @param event Key event.
 */
void ToolGOZoom::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::SHIFT)
    {
        this->graphicsView()->zoomOut(10);
    }
    else
    {
        this->graphicsView()->zoomIn(10);
    }
}
