#ifndef TOOLGOPOINTEREXTEND_H
#define TOOLGOPOINTEREXTEND_H
/**
 * The extended pointer tool, it is able to move the scene, move the item,
 * and connect GO operators with signal.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgoabstract.h"

class ItemGOSignal;
class ItemDrawable;

class ToolGOPointerExtend : public ToolGOAbstract
{
public:
    ToolGOPointerExtend(SceneGO *sceneGO);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

protected:
    enum Status
    {
        Status_Null,                // Nothing is selected, the mouse and key is released.
        Status_Scene_Moving,        // Moving the scene.
        Status_Item_Moving,         // Moving the item.
        Status_Signal_Connecting    // Connect operators with signals.
    };
    Status _status;
    ItemDrawable* _item;
    ItemGOSignal* _signal;

    bool isAround(QPointF pos1, QPointF pos2);
    void mousePressStatusNull(QGraphicsSceneMouseEvent *event);
    bool mousePressStatusNullSignal(QGraphicsSceneMouseEvent *event);
    virtual bool mousePressStatusNullItem(QGraphicsSceneMouseEvent *event);
    bool mousePressStatusNullScene(QGraphicsSceneMouseEvent *event);
    void mouseMoveStatusNull(QGraphicsSceneMouseEvent *event);
    bool mouseMoveStatusNullSignal(QGraphicsSceneMouseEvent *event);
    bool mouseMoveStatusNullItem(QGraphicsSceneMouseEvent *event);
    bool mouseMoveStatusNullScene(QGraphicsSceneMouseEvent *event);
    void mouseReleaseStatusNull(QGraphicsSceneMouseEvent *event);

    void mouseMoveStatusItemMoving(QGraphicsSceneMouseEvent *event);
    void mouseReleaseStatusItemMoving(QGraphicsSceneMouseEvent *event);

    void mouseReleaseStatusSceneMoving(QGraphicsSceneMouseEvent *event);

    void mouseMoveStatusSignalConnecting(QGraphicsSceneMouseEvent *event);
    void mouseReleaseStatusSignalConnecting(QGraphicsSceneMouseEvent *event);
};

#endif // TOOLGOPOINTEREXTEND_H
