#include "toolgozoom.h"

ToolGOZoom::ToolGOZoom(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->graphicsView()->setCursor(Qt::PointingHandCursor);
}

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
