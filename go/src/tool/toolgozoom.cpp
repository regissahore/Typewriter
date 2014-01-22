#include "ToolGoZoom.h"

ToolGoZoom::ToolGoZoom(SceneGo *sceneGo) : ToolGoAbstract(sceneGo)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->graphicsView()->setCursor(Qt::PointingHandCursor);
}

void ToolGoZoom::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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
