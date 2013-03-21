#ifndef TOOLGOPOINTER_H
#define TOOLGOPOINTER_H
/**
 * The pointer tool of the GO Graph.
 * The pointer tool is used to selecting single items in the graphics scene.
 * Besides it could move moveable items in the scene.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QGraphicsView>
#include "toolgoabstract.h"
#include "itemmoveable.h"
#include "messagefactorytool.h"
#include "definationeditorselectiontype.h"

class ToolGOPointer : public ToolGOAbstract
{
public:
    ToolGOPointer(SceneGO *sceneGO);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

protected:
    ItemMoveable* _item;
    bool _moving;
    virtual void setMoving(bool value);
};

#endif // TOOLGOPOINTER_H
