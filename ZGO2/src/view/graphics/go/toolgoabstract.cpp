#include "toolgoabstract.h"

/**
 * The constructor. The pointer of ViewGO entity must be set.
 * @param viewGO The pointer to the ViewGO entity.
 */
ToolGOAbstract::ToolGOAbstract(SceneGO *sceneGO)
{
    this->_sceneGO = sceneGO;
}

/**
 * Get the pointer of the ViewGO entity.
 * @return The pointer to ViewGO entity.
 */
SceneGO* ToolGOAbstract::sceneGO() const
{
    return this->_sceneGO;
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

