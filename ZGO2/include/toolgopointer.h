#ifndef TOOLGOPOINTER_H
#define TOOLGOPOINTER_H
#include <QGraphicsView>
#include "toolgoabstract.h"
#include "itemmoveable.h"
#include "definationeditorselectiontype.h"

class ToolGOPointer : public ToolGOAbstract
{
public:
    ToolGOPointer(SceneGO *sceneGO);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

protected:
    ItemDrawable* _item;
    bool _moving;
    virtual void setMoving(bool value);
};

#endif // TOOLGOPOINTER_H
