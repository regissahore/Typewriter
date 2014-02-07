#include "ToolGoMove.h"

ToolGoMove::ToolGoMove(SceneGo *sceneGo) : ToolGoAbstract(sceneGo)
{
    this->graphicsView()->setDragMode(QGraphicsView::ScrollHandDrag);
    this->graphicsView()->setInteractive(true);
}

