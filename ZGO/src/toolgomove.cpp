#include "toolgomove.h"

ToolGOMove::ToolGOMove(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setDragMode(QGraphicsView::ScrollHandDrag);
    this->graphicsView()->setInteractive(true);
}

