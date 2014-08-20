#include "ToolGoAbstract.h"
#include "SceneGo.h"

ToolGoAbstract::ToolGoAbstract(SceneGo *sceneGo)
{
    this->_sceneGo = sceneGo;
    this->_graphicsScene = (QGraphicsScene*)sceneGo;
    this->_graphicsView = (GraphicsView*)this->_graphicsScene->parent();
}

ToolGoAbstract::~ToolGoAbstract()
{
}

void ToolGoAbstract::activate()
{
}

SceneGo* ToolGoAbstract::sceneGo() const
{
    return this->_sceneGo;
}

QGraphicsScene* ToolGoAbstract::graphicsScene() const
{
    return this->_graphicsScene;
}

GraphicsView* ToolGoAbstract::graphicsView() const
{
    return this->_graphicsView;
}

void ToolGoAbstract::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void ToolGoAbstract::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void ToolGoAbstract::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ToolGoAbstract::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ToolGoAbstract::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ToolGoAbstract::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ToolGoAbstract::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    Q_UNUSED(event);
}

