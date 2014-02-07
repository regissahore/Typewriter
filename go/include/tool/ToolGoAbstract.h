#ifndef TOOLGOABSTRACT_H
#define TOOLGOABSTRACT_H
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include "GraphicsView.h"
#include "TypedItem.h"

class SceneGo;

class ToolGoAbstract : public TypedItem
{
public:
    ToolGoAbstract(SceneGo *sceneGo);
    virtual ~ToolGoAbstract();
    virtual void activate();
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);
protected:
    SceneGo* sceneGo() const;
    QGraphicsScene* graphicsScene() const;
    GraphicsView* graphicsView() const;
private:
    SceneGo *_sceneGo;
    QGraphicsScene *_graphicsScene;
    GraphicsView *_graphicsView;
};

#endif // TOOLGOABSTRACT_H
