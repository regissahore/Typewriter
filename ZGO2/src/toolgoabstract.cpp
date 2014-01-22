#include "toolgoabstract.h"
#include "scenego.h"

ToolGOAbstract::ToolGOAbstract(SceneGO *sceneGO)
{
    this->_sceneGO = sceneGO;
    this->_graphicsScene = (QGraphicsScene*)sceneGO;
    this->_graphicsView = (GraphicsView*)this->_graphicsScene->parent();
}

ToolGOAbstract::~ToolGOAbstract()
{
}

void ToolGOAbstract::activate()
{
}

SceneGO* ToolGOAbstract::sceneGO() const
{
    return this->_sceneGO;
}

QGraphicsScene* ToolGOAbstract::graphicsScene() const
{
    return this->_graphicsScene;
}

GraphicsView* ToolGOAbstract::graphicsView() const
{
    return this->_graphicsView;
}

void ToolGOAbstract::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void ToolGOAbstract::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void ToolGOAbstract::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ToolGOAbstract::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ToolGOAbstract::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ToolGOAbstract::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ToolGOAbstract::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    Q_UNUSED(event);
}

