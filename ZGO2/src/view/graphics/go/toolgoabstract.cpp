#include "toolgoabstract.h"
#include "scenego.h"

/**
 * The constructor. The pointer of SceneGO entity must be set.
 * @param viewGO The pointer to the SceneGO entity.
 */
ToolGOAbstract::ToolGOAbstract(SceneGO *sceneGO)
{
    this->_sceneGO = sceneGO;
    this->_graphicsScene = (QGraphicsScene*)sceneGO;
    this->_graphicsView = (GraphicsView*)this->_graphicsScene->parent();
}

/**
 * Activate the tool.
 */
void ToolGOAbstract::activate()
{
}

/**
 * Get the pointer of the SceneGO entity.
 * @return The pointer to SceneGO entity.
 */
SceneGO* ToolGOAbstract::sceneGO() const
{
    return this->_sceneGO;
}

/**
 * Get the pointer of the QGraphicsScene entity.
 * @return The pointer to QGraphicsScene entity.
 */
QGraphicsScene* ToolGOAbstract::graphicsScene() const
{
    return this->_graphicsScene;
}

/**
 * Get the pointer of the GraphicsView entity.
 * @return The pointer to GraphicsView entity.
 */
GraphicsView* ToolGOAbstract::graphicsView() const
{
    return this->_graphicsView;
}

/**
 * The key press event.
 * @param event Qt key event.
 */
void ToolGOAbstract::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

/**
 * The key release event.
 * @param event Qt key event.
 */
void ToolGOAbstract::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

/**
 * The mouse double click event.
 * @param event Qt mouse event of graphics scene.
 */
void ToolGOAbstract::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

/**
 * The mouse move event.
 * @param event Qt mouse event of graphics scene.
 */
void ToolGOAbstract::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

/**
 * The mouse press event.
 * @param event Qt mouse event of graphics scene.
 */
void ToolGOAbstract::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

/**
 * The mouse release event.
 * @param event Qt mouse event of graphics scene.
 */
void ToolGOAbstract::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

/**
 * The mouse wheel event.
 * @param event Qt wheel event of graphics scene.
 */
void ToolGOAbstract::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    Q_UNUSED(event);
}

