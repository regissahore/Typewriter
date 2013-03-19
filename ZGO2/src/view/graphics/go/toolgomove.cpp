#include "toolgomove.h"

/**
 * The constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOMove::ToolGOMove(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setDragMode(QGraphicsView::ScrollHandDrag);
    this->graphicsView()->setInteractive(true);
}

