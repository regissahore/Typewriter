#ifndef TOOLGOPOINTER_H
#define TOOLGOPOINTER_H
#include <QGraphicsView>
#include "ToolGoAbstract.h"
#include "ItemMoveable.h"
#include "DefinationEditorSelectionType.h"

class ToolGoPointer : public ToolGoAbstract
{
public:
    ToolGoPointer(SceneGo *sceneGo);
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
