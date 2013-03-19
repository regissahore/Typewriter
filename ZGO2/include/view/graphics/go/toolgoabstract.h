#ifndef TOOLGOABSTRACT_H
#define TOOLGOABSTRACT_H
/**
 * An abstract tool of GO Graph.
 * The function of the tool is to implement the interaction of the user.
 * The tool will get the the pointer of the SceneGO entity, and tend to use the
 * public functions of the SceneGO entity.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include "graphicsview.h"
#include "typeditem.h"

class SceneGO;

class ToolGOAbstract : public TypedItem
{
public:
    ToolGOAbstract(SceneGO *sceneGO);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);
protected:
    SceneGO* sceneGO() const;
    QGraphicsScene* graphicsScene() const;
    GraphicsView* graphicsView() const;
private:
    SceneGO *_sceneGO;
    QGraphicsScene *_graphicsScene;
    GraphicsView *_graphicsView;
};

#include "scenego.h"

#endif // TOOLGOABSTRACT_H
