#ifndef TOOLGOABSTRACT_H
#define TOOLGOABSTRACT_H
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
    virtual ~ToolGOAbstract();
    virtual void activate();
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

#endif // TOOLGOABSTRACT_H
